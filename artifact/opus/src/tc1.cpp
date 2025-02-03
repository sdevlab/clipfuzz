#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "opus_multistream.h"
#include "opus.h"

//#include "test_opus_common.h"
#define opus_test_assert(cond) {if (!(cond)) {return 0;}}

static int celt_ec_internal_error(void)
{
    OpusMSEncoder *enc;
    int err;
    unsigned char data[2460];
    int streams;
    int coupled_streams;
    unsigned char mapping[1];

    enc = opus_multistream_surround_encoder_create(16000, 1, 1, &streams,
        &coupled_streams, mapping, OPUS_APPLICATION_VOIP, &err);
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(8));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(OPUS_AUTO));
    {
        static const short pcm[320] =
        {
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,  1792,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,     0, 25600,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799,     7,     0,   255,     0,     0,
                 0,     0,     0,     0,     0,     0,     0, 32767,    -1,
                 0,     0,     0,   100,     0, 16384,     0,     0,     0,
                 0,     0,     0,     4,     0,     0,  -256,   255,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,-32768,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,   128,     0,     0,     0,     0,
                 0,     0,     0,     0,  -256,     0,     0,    32,     0,
                 0,     0,     0,     0,     0,     0,  4352,     4,   228,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,  5632,     0,     0,
                 0,     0,-32768,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,   256,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
             -3944, 10500,  4285, 10459, -6474, 10204, -6539, 11601, -6824,
             13385, -7142, 13872,-11553, 13670, -7725, 13463, -6887,  7874,
             -5580, 12600, -4964, 12480,  3254, 11741, -4210,  9741, -3155,
              7558, -5468,  5431, -1073,  3641, -1304,     0,    -1,   343,
                26,     0,     0,   150,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,  1799,  1799,  1799,  1799,  1799, -2553,
                 7,  1792,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799, -9721
        };
        err = opus_multistream_encode(enc, pcm, 320, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9526, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, 25600, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9494, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9479, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510, -9510,
             -9510, -9510, -9510, -9510, -9510, -9510, -9510
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_MUSIC));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(10));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_BANDWIDTH_FULLBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(18));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(90));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(280130));
    {
        static const short pcm[160] =
        {
             -9510, -9510,  1799,  1799,  1799,  1799,  1799,  1799,  1799,
              1799,  1799,  1799,  1799,  1799,  1799,  1799,  1799,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
              -256,   255,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,     0,     0,     0,   128,     0,
                 0,     0,     0,     0,     0,     0,     0,     0,     0,
                 0,    32,     0,     0,     0,     0,     0,     0,     0,
              4352,     4,     0,     0,     0,     0,     0,     0,     0,
                 0,     0,     0,     0,   148,     0,     0,     0,     0,
              5632
        };
        err = opus_multistream_encode(enc, pcm, 160, data, 2460);
        opus_test_assert(err > 0);
    }
    opus_multistream_encoder_ctl(enc, OPUS_SET_SIGNAL(OPUS_SIGNAL_VOICE));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PREDICTION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PHASE_INVERSION_DISABLED(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(1));
    opus_multistream_encoder_ctl(enc, OPUS_SET_COMPLEXITY(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_MAX_BANDWIDTH(OPUS_BANDWIDTH_NARROWBAND));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BANDWIDTH(OPUS_AUTO));
    opus_multistream_encoder_ctl(enc, OPUS_SET_LSB_DEPTH(12));
    opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(0));
    opus_multistream_encoder_ctl(enc, OPUS_SET_PACKET_LOSS_PERC(41));
    opus_multistream_encoder_ctl(enc, OPUS_SET_BITRATE(21425));
    {
        static const short pcm[40] =
        {
             10459, -6474, 10204, -6539, 11601, -6824, 13385, -7142, 13872,
            -11553, 13670, -7725, 13463, -6887, 12482, -5580, 12600, -4964,
             12480,  3254, 11741, -4210,  9741, -3155,  7558, -5468,  5431,
             -1073,  3641, -1304,     0,    -1,   343,    26,     0,     0,
                 0,     0,  -256,   226
        };
        err = opus_multistream_encode(enc, pcm, 40, data, 2460);
        opus_test_assert(err > 0);
        /* returns -3 */
    }
    opus_multistream_encoder_destroy(enc);
    return 0;
}

int main () {
  
  celt_ec_internal_error();

  return 0;
}
