#include <iostream>
#include <fstream>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "opus.h"
#include "opus_defines.h"
#include "opus_multistream.h"
#include "opus_types.h"
#include "../celt/os_support.h"

#define MAX_PACKET (1500)
static unsigned char out[MAX_PACKET];

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  opus_int32 nb_channels = fdp.ConsumeIntegralInRange(0, 255);
  const opus_int32 frequency = fdp.PickValueInArray({8, 12, 16, 24, 48}) * 1000;
  int streams = fdp.ConsumeIntegralInRange(0, 255);
  int coupled_streams = fdp.ConsumeIntegralInRange(0, 255);
  int frame_size_ms_x2 =
      fdp.PickValueInArray({5, 10, 20, 40, 80, 120, 160, 200, 240});
  int frame_size = frame_size_ms_x2 * frequency / 2000;
  int application =
      fdp.PickValueInArray({OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_VOIP,
                            OPUS_APPLICATION_RESTRICTED_LOWDELAY});

  unsigned char *mapping = (unsigned char *)malloc(nb_channels);
  if (!mapping) {
    return 0;
  }
  for (unsigned char x = 0; x < nb_channels; ++x) {
    mapping[x] = fdp.ConsumeIntegralInRange(0, 255);
  }

  int err = OPUS_OK;
  OpusMSEncoder *enc = NULL;
  if (fdp.ConsumeBool()) {
    int mapping_family = fdp.PickValueInArray({0, 1, 2, 3, 255});
    enc = opus_multistream_surround_encoder_create(
        frequency, nb_channels, mapping_family, &streams, &coupled_streams,
        mapping, application, &err);
  } else {
    enc = opus_multistream_encoder_create(frequency, nb_channels, streams,
                                          coupled_streams, mapping, application,
                                          &err);
  }
  free(mapping);
  if (err != OPUS_OK || enc == NULL) {
    opus_multistream_encoder_destroy(enc);
    return 0;
  }

  int t;
  t =  fdp.ConsumeIntegralInRange(0, 10);
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_COMPLEXITY(t));
  t =  fdp.ConsumeBool();
  opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(t));
  t =  fdp.ConsumeBool();
  opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(t));
  t =  fdp.PickValueInArray({OPUS_AUTO, 1, 2});
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_FORCE_CHANNELS(t));
  t =  fdp.PickValueInArray(
               {OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND,
                OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND,
                OPUS_BANDWIDTH_FULLBAND});
  opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(t));
  t = fdp.ConsumeBool();
  opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(t));
  t = fdp.ConsumeIntegralInRange(0, 100);
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_PACKET_LOSS_PERC(t));
  t = fdp.ConsumeBool();
  opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(t));
  t = fdp.ConsumeIntegralInRange(8, 24);
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_LSB_DEPTH(t));
  t = fdp.ConsumeBool();
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_PREDICTION_DISABLED(t));
  t = fdp.PickValueInArray(
               {OPUS_AUTO, OPUS_SIGNAL_VOICE, OPUS_SIGNAL_MUSIC});
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_SIGNAL(t));
  t = fdp.ConsumeBool();
  opus_multistream_encoder_ctl(
      enc, OPUS_SET_PHASE_INVERSION_DISABLED(t));

  const int pcm_size = sizeof(opus_int16) * frame_size * nb_channels;
  opus_int16 *pcm = (opus_int16 *)opus_alloc(pcm_size);
  if (pcm == NULL) {
    opus_multistream_encoder_destroy(enc);
    return 0;
  }
  memset(pcm, 0, pcm_size);

  if (pcm_size == fdp.ConsumeData(pcm, pcm_size)) {
    const int len =
        opus_multistream_encode(enc, pcm, frame_size, out, MAX_PACKET);
    (void)len;
  }

  opus_free(pcm);
  opus_multistream_encoder_destroy(enc);

  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        std::cerr << "Failed to read from file: " << argv[1] << std::endl;
        return 1;
    }

    LLVMFuzzerTestOneInput(buffer.data(), buffer.size());

    return 0;
}
