#include "gfuzz_opus.h"

//#define MAX_API_SEQ_LEN 0
#define OBJ_POOL_SIZE 0
#define PRIMITIVE_POOL_SIZE 0
#define BUFFER_POOL_SIZE 0
#define API_BLOCK_N 22
#define MAX_BUFFER_SIZE 1048576
static int MAX_API_SEQ_LEN = 0;

#include "api_block.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "port/protobuf.h"
#include "src/libfuzzer/libfuzzer_macro.h"


int check_validity (const FUZZING_BYTES& fuzzing_bytes);
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes);
void update_max_api_seq_len () {
    if (MAX_API_SEQ_LEN == 0) {
        MAX_API_SEQ_LEN = atoi(getenv("MAX_API_SEQ_LEN"));
    }
}

OpusMSEncoder* pool_buf_OpusMSEncoder_p[BUFFER_POOL_SIZE];
uint32_t pool__uint32_t[PRIMITIVE_POOL_SIZE];
opus_int16* pool_buf_opus_int16_p[BUFFER_POOL_SIZE];
uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
int pool__int[PRIMITIVE_POOL_SIZE];
opus_int32 pool__opus_int32[PRIMITIVE_POOL_SIZE];
unsigned char* pool_buf_unsigned_char_p[BUFFER_POOL_SIZE];
bool pool__bool[PRIMITIVE_POOL_SIZE];

void call_driver_31_to_71 (const APIB_CALL_INPUT& ref);
void call_driver_72 (const APIB_CALL_INPUT& ref);
void call_driver_73 (const APIB_CALL_INPUT& ref);
void call_driver_74_to_75 (const APIB_CALL_INPUT& ref);
void call_driver_76_to_80 (const APIB_CALL_INPUT& ref);
void call_driver_81 (const APIB_CALL_INPUT& ref);
void call_driver_82_to_83 (const APIB_CALL_INPUT& ref);
void call_driver_84 (const APIB_CALL_INPUT& ref);
void call_driver_85_to_86 (const APIB_CALL_INPUT& ref);
void call_driver_87_to_88 (const APIB_CALL_INPUT& ref);
void call_driver_89_to_91 (const APIB_CALL_INPUT& ref);
void call_driver_92_to_93 (const APIB_CALL_INPUT& ref);
void call_driver_95_to_109 (const APIB_CALL_INPUT& ref);
void call_driver_110 (const APIB_CALL_INPUT& ref);
void call_driver_opus_multistream_surround_encoder_create (const APIB_CALL_INPUT& ref);
void call_driver_opus_multistream_encoder_create (const APIB_CALL_INPUT& ref);
void call_driver_opus_multistream_encoder_destroy (const APIB_CALL_INPUT& ref);
void call_driver_opus_multistream_encode (const APIB_CALL_INPUT& ref);
void call_driver_54_to_63 (const APIB_CALL_INPUT& ref);
void call_driver_65_to_68 (const APIB_CALL_INPUT& ref);
void call_driver_97_to_100 (const APIB_CALL_INPUT& ref);
void call_driver_103_to_107 (const APIB_CALL_INPUT& ref);


int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  //if (fuzzing_bytes.pool_init_values().buf_opusmsencoder_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._uint32_t_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_opus_int16_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._int_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._opus_int32_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_unsigned_char_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._bool_size() != PRIMITIVE_POOL_SIZE) { return 1; }

  if (fuzzing_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) { return 1; }

  for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (fuzzing_bytes.pool_init_values().buf_opus_int16_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_unsigned_char_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
  }
  return 0;
}
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes) {
  for (int i = 0; i < fuzzing_bytes.api_block_call_seq_size(); i++) {

    fuzzing_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzing_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzing_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_opusmsencoder_p_0(api_block_call_input->in_idx_opusmsencoder_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_opusmsencoder_p_0(api_block_call_input->out_idx_opusmsencoder_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__uint32_t_0(api_block_call_input->in_idx__uint32_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_1(api_block_call_input->in_idx__uint32_t_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_2(api_block_call_input->in_idx__uint32_t_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_3(api_block_call_input->in_idx__uint32_t_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_4(api_block_call_input->in_idx__uint32_t_4() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_5(api_block_call_input->in_idx__uint32_t_5() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_6(api_block_call_input->in_idx__uint32_t_6() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__uint32_t_7(api_block_call_input->in_idx__uint32_t_7() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_0(api_block_call_input->out_idx__uint32_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_1(api_block_call_input->out_idx__uint32_t_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_2(api_block_call_input->out_idx__uint32_t_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_3(api_block_call_input->out_idx__uint32_t_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_4(api_block_call_input->out_idx__uint32_t_4() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_5(api_block_call_input->out_idx__uint32_t_5() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_6(api_block_call_input->out_idx__uint32_t_6() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint32_t_7(api_block_call_input->out_idx__uint32_t_7() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_opus_int16_p_0(api_block_call_input->in_idx_buf_opus_int16_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_opus_int16_p_0(api_block_call_input->out_idx_buf_opus_int16_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);

    api_block_call_input->set_in_idx__int_0(api_block_call_input->in_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_1(api_block_call_input->in_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_2(api_block_call_input->in_idx__int_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_3(api_block_call_input->in_idx__int_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_4(api_block_call_input->in_idx__int_4() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_5(api_block_call_input->in_idx__int_5() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_0(api_block_call_input->out_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_1(api_block_call_input->out_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_2(api_block_call_input->out_idx__int_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_3(api_block_call_input->out_idx__int_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_4(api_block_call_input->out_idx__int_4() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_5(api_block_call_input->out_idx__int_5() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__opus_int32_0(api_block_call_input->in_idx__opus_int32_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__opus_int32_1(api_block_call_input->in_idx__opus_int32_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__opus_int32_0(api_block_call_input->out_idx__opus_int32_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__opus_int32_1(api_block_call_input->out_idx__opus_int32_1() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_unsigned_char_p_0(api_block_call_input->in_idx_buf_unsigned_char_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_unsigned_char_p_0(api_block_call_input->out_idx_buf_unsigned_char_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__bool_0(api_block_call_input->in_idx__bool_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__bool_0(api_block_call_input->out_idx__bool_0() % PRIMITIVE_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
      pool__uint32_t[i] = (uint32_t)serialized_bytes.pool_init_values()._uint32_t(i).val();

      pool__int[i] = (int)serialized_bytes.pool_init_values()._int(i).val();

      pool__opus_int32[i] = (opus_int32)serialized_bytes.pool_init_values()._opus_int32(i).val();

      pool__bool[i] = (bool)serialized_bytes.pool_init_values()._bool(i).val();

    }


    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_opus_int16_p(i).val();
      buf += '\0';
      pool_buf_opus_int16_p[i] = (opus_int16*)malloc(buf.length());
      std::memcpy((void*)pool_buf_opus_int16_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_unsigned_char_p(i).val();
      buf += '\0';
      pool_buf_unsigned_char_p[i] = (unsigned char*)malloc(buf.length());
      std::memcpy((void*)pool_buf_unsigned_char_p[i], buf.data(), buf.size());

    }


  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_31_to_71(api_block_call_input);
        break;

      case 1:
        call_driver_72(api_block_call_input);
        break;

      case 2:
        call_driver_73(api_block_call_input);
        break;

      case 3:
        call_driver_74_to_75(api_block_call_input);
        break;

      case 4:
        call_driver_76_to_80(api_block_call_input);
        break;

      case 5:
        call_driver_81(api_block_call_input);
        break;

      case 6:
        call_driver_82_to_83(api_block_call_input);
        break;

      case 7:
        call_driver_84(api_block_call_input);
        break;

      case 8:
        call_driver_85_to_86(api_block_call_input);
        break;

      case 9:
        call_driver_87_to_88(api_block_call_input);
        break;

      case 10:
        call_driver_89_to_91(api_block_call_input);
        break;

      case 11:
        call_driver_92_to_93(api_block_call_input);
        break;

      case 12:
        call_driver_95_to_109(api_block_call_input);
        break;

      case 13:
        call_driver_110(api_block_call_input);
        break;

      case 14:
        call_driver_opus_multistream_surround_encoder_create(api_block_call_input);
        break;

      case 15:
        call_driver_opus_multistream_encoder_create(api_block_call_input);
        break;

      case 16:
        call_driver_opus_multistream_encoder_destroy(api_block_call_input);
        break;

      case 17:
        call_driver_opus_multistream_encode(api_block_call_input);
        break;

      case 18:
        call_driver_54_to_63(api_block_call_input);
        break;

      case 19:
        call_driver_65_to_68(api_block_call_input);
        break;

      case 20:
        call_driver_97_to_100(api_block_call_input);
        break;

      case 21:
        call_driver_103_to_107(api_block_call_input);
        break;
    };
  }
}

void call_driver_31_to_71 (const APIB_CALL_INPUT& ref) {
  uint32_t _t0_ = pool__uint32_t[ref.in_idx__uint32_t_0()];
  uint32_t _t1_ = pool__uint32_t[ref.in_idx__uint32_t_1()];
  uint32_t _t2_ = pool__uint32_t[ref.in_idx__uint32_t_2()];
  uint32_t _t3_ = pool__uint32_t[ref.in_idx__uint32_t_3()];
  uint32_t _t4_ = pool__uint32_t[ref.in_idx__uint32_t_4()];
  uint32_t _t5_ = pool__uint32_t[ref.in_idx__uint32_t_5()];
  uint32_t _t6_ = pool__uint32_t[ref.in_idx__uint32_t_6()];
  uint32_t _t7_ = pool__uint32_t[ref.in_idx__uint32_t_7()];
  bool _t9_ = pool__bool[ref.in_idx__bool_0()];
  const uint8_t* _t10_ = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];

  //FuzzedDataProvider fdp(data, size);

  opus_int32 nb_channels = (_t0_ % 256) + 0;
  const opus_int32 frequency = ((int[]){8, 12, 16, 24, 48}[_t1_%5]) * 1000;
  int streams = (_t2_ % 256) + 0;
  int coupled_streams = (_t5_ % 256) + 0;
  int frame_size_ms_x2 =
      ((int[]){5, 10, 20, 40, 80, 120, 160, 200, 240}[_t3_%9]);
  int frame_size = frame_size_ms_x2 * frequency / 2000;
  int application =
      ((int[]){OPUS_APPLICATION_AUDIO, OPUS_APPLICATION_VOIP, OPUS_APPLICATION_RESTRICTED_LOWDELAY}[_t4_%3]);

  unsigned char *mapping = (unsigned char *)malloc(nb_channels);
  if (!mapping) {
    return;
  }

  strlen((const char *)memcpy((void*)mapping, _t10_, nb_channels));
  for (unsigned char x = 0; x < nb_channels; ++x) {
    mapping[x] = mapping[x] % 256;
  }

  int err = OPUS_OK;
  OpusMSEncoder *enc = NULL;
  if (_t9_) {
    int mapping_family = ((int[]){0, 1, 2, 3, 255}[_t6_%5]);
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
    return;
  }

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_COMPLEXITY((_t7_ % 11) + 0));

  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t0_;
  pool__uint32_t[ref.out_idx__uint32_t_1()] = _t1_;
  pool__uint32_t[ref.out_idx__uint32_t_2()] = _t2_;
  pool__uint32_t[ref.out_idx__uint32_t_3()] = _t3_;
  pool__uint32_t[ref.out_idx__uint32_t_4()] = _t4_;
  pool__uint32_t[ref.out_idx__uint32_t_5()] = _t5_;
  pool__uint32_t[ref.out_idx__uint32_t_6()] = _t6_;
  pool__uint32_t[ref.out_idx__uint32_t_7()] = _t7_;
  pool__bool[ref.out_idx__bool_0()] = _t9_;
  pool__opus_int32[ref.out_idx__opus_int32_0()] = nb_channels ;
  pool__opus_int32[ref.out_idx__opus_int32_1()] = frequency ;
  pool__int[ref.out_idx__int_0()] = streams ;
  pool__int[ref.out_idx__int_1()] = coupled_streams ;
  pool__int[ref.out_idx__int_2()] = frame_size_ms_x2 ;
  pool__int[ref.out_idx__int_3()] = frame_size ;
  pool__int[ref.out_idx__int_4()] = application ;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = mapping ;
  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc ;
}

void call_driver_72 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  opus_multistream_encoder_ctl(enc, OPUS_SET_VBR(_t0_));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_73 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  opus_multistream_encoder_ctl(enc, OPUS_SET_VBR_CONSTRAINT(_t0_));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_74_to_75 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  uint32_t _t0_ = pool__uint32_t[ref.in_idx__uint32_t_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_FORCE_CHANNELS(((int[]){OPUS_AUTO, 1, 2}[_t0_%3])));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t0_;
}

void call_driver_76_to_80 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  uint32_t _t0_ = pool__uint32_t[ref.in_idx__uint32_t_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_MAX_BANDWIDTH(((int[]){OPUS_BANDWIDTH_NARROWBAND, OPUS_BANDWIDTH_MEDIUMBAND, OPUS_BANDWIDTH_WIDEBAND, OPUS_BANDWIDTH_SUPERWIDEBAND, OPUS_BANDWIDTH_FULLBAND}[_t0_%5])));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t0_;
}

void call_driver_81 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  opus_multistream_encoder_ctl(enc, OPUS_SET_INBAND_FEC(_t0_));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_82_to_83 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  uint32_t _t0_ = pool__uint32_t[ref.in_idx__uint32_t_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_PACKET_LOSS_PERC((_t0_ % 101) + 0));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t0_;
}

void call_driver_84 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  opus_multistream_encoder_ctl(enc, OPUS_SET_DTX(_t0_));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_85_to_86 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  uint32_t _t0_ = pool__uint32_t[ref.in_idx__uint32_t_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_LSB_DEPTH((_t0_ % 33) + 8));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t0_;
}

void call_driver_87_to_88 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_PREDICTION_DISABLED((_t0_)));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_89_to_91 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  uint32_t _t0_ = pool__uint32_t[ref.in_idx__uint32_t_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_SIGNAL(((int[]){OPUS_AUTO, OPUS_SIGNAL_VOICE, OPUS_SIGNAL_MUSIC}[_t0_%3])));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t0_;
}

void call_driver_92_to_93 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  opus_multistream_encoder_ctl(
      enc, OPUS_SET_PHASE_INVERSION_DISABLED(((_t0_))));

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
}

void call_driver_95_to_109 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  int frame_size = pool__int[ref.in_idx__int_0()];
  opus_int32 nb_channels = pool__opus_int32[ref.in_idx__opus_int32_0()];
  const uint8_t* _t1_ = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];

  const int pcm_size = sizeof(opus_int16) * frame_size * nb_channels;
  opus_int16 *pcm = (opus_int16 *)opus_alloc(pcm_size);
  if (pcm == NULL) {
    opus_multistream_encoder_destroy(enc);
    return;
  }
  memset(pcm, 0, pcm_size);

    if (pcm_size == pcm_size) {
    const int len =
        opus_multistream_encode(enc, pcm, frame_size, out, MAX_PACKET);
    (void)len;
  }
  memcpy((void*)pcm, _t1_, pcm_size);
  opus_free(pcm);

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__int[ref.out_idx__int_0()] = frame_size;
  pool__opus_int32[ref.out_idx__opus_int32_0()] = nb_channels;
  pool__int[ref.out_idx__int_1()] = pcm_size ;
  pool_buf_opus_int16_p[ref.out_idx_buf_opus_int16_p_0()] = pcm ;
}

void call_driver_110 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];

  opus_multistream_encoder_destroy(enc);

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
}

void call_driver_opus_multistream_surround_encoder_create (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  const opus_int32 frequency = pool__opus_int32[ref.in_idx__opus_int32_0()];
  opus_int32 nb_channels = pool__opus_int32[ref.in_idx__opus_int32_1()];
  int mapping_family = pool__int[ref.in_idx__int_0()];
  int streams = pool__int[ref.in_idx__int_1()];
  int coupled_streams = pool__int[ref.in_idx__int_2()];
  unsigned char* mapping = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];
  int application = pool__int[ref.in_idx__int_3()];
  int err = pool__int[ref.in_idx__int_4()];

    enc = opus_multistream_surround_encoder_create(
        frequency, nb_channels, mapping_family, &streams, &coupled_streams,
        mapping, application, &err);

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__opus_int32[ref.out_idx__opus_int32_0()] = nb_channels;
  pool__int[ref.out_idx__int_0()] = mapping_family;
  pool__int[ref.out_idx__int_1()] = streams;
  pool__int[ref.out_idx__int_2()] = coupled_streams;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = mapping;
  pool__int[ref.out_idx__int_3()] = application;
  pool__int[ref.out_idx__int_4()] = err;
}

void call_driver_opus_multistream_encoder_create (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  const opus_int32 frequency = pool__opus_int32[ref.in_idx__opus_int32_0()];
  opus_int32 nb_channels = pool__opus_int32[ref.in_idx__opus_int32_1()];
  int streams = pool__int[ref.in_idx__int_0()];
  int coupled_streams = pool__int[ref.in_idx__int_1()];
  unsigned char* mapping = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];
  int application = pool__int[ref.in_idx__int_2()];
  int err = pool__int[ref.in_idx__int_3()];

    enc = opus_multistream_encoder_create(frequency, nb_channels, streams,
                                          coupled_streams, mapping, application,
                                          &err);

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__opus_int32[ref.out_idx__opus_int32_0()] = nb_channels;
  pool__int[ref.out_idx__int_0()] = streams;
  pool__int[ref.out_idx__int_1()] = coupled_streams;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = mapping;
  pool__int[ref.out_idx__int_2()] = application;
  pool__int[ref.out_idx__int_3()] = err;
}

void call_driver_opus_multistream_encoder_destroy (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];

    opus_multistream_encoder_destroy(enc);

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
}

void call_driver_opus_multistream_encode (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  const opus_int32 frame_size = pool__opus_int32[ref.in_idx__opus_int32_0()];
  opus_int16* pcm = pool_buf_opus_int16_p[ref.in_idx_buf_opus_int16_p_0()];

    const int len =
        opus_multistream_encode(enc, pcm, frame_size, out, MAX_PACKET);

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool_buf_opus_int16_p[ref.out_idx_buf_opus_int16_p_0()] = pcm;
  pool__int[ref.out_idx__int_0()] = len ;
}

void call_driver_54_to_63 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  const opus_int32 frame_size = pool__opus_int32[ref.in_idx__opus_int32_0()];
  opus_int16* pcm = pool_buf_opus_int16_p[ref.in_idx_buf_opus_int16_p_0()];
  int streams = pool__int[ref.in_idx__int_0()];
  unsigned char* mapping = pool_buf_unsigned_char_p[ref.in_idx_buf_unsigned_char_p_0()];
  int coupled_streams = pool__int[ref.in_idx__int_1()];
  int application = pool__int[ref.in_idx__int_2()];
  int err = pool__int[ref.in_idx__int_3()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];
  uint32_t _t1_ = pool__uint32_t[ref.in_idx__uint32_t_0()];

  if (_t0_) {
    int mapping_family = ((int[]){0, 1, 2, 3, 255}[_t1_%5]);
    enc = opus_multistream_surround_encoder_create(
        frequency, nb_channels, mapping_family, &streams, &coupled_streams,
        mapping, application, &err);
  } else {
    enc = opus_multistream_encoder_create(frequency, nb_channels, streams,
                                          coupled_streams, mapping, application,
                                          &err);
  }

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool_buf_opus_int16_p[ref.out_idx_buf_opus_int16_p_0()] = pcm;
  pool__int[ref.out_idx__int_0()] = streams;
  pool_buf_unsigned_char_p[ref.out_idx_buf_unsigned_char_p_0()] = mapping;
  pool__int[ref.out_idx__int_1()] = coupled_streams;
  pool__int[ref.out_idx__int_2()] = application;
  pool__int[ref.out_idx__int_3()] = err;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
  pool__uint32_t[ref.out_idx__uint32_t_0()] = _t1_;
}

void call_driver_65_to_68 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  int err = pool__int[ref.in_idx__int_0()];

  if (err != OPUS_OK || enc == NULL) {
    opus_multistream_encoder_destroy(enc);
    return;
  }

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool__int[ref.out_idx__int_0()] = err;
}

void call_driver_97_to_100 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  opus_int16* pcm = pool_buf_opus_int16_p[ref.in_idx_buf_opus_int16_p_0()];

  if (pcm == NULL) {
    opus_multistream_encoder_destroy(enc);
    return;
  }

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool_buf_opus_int16_p[ref.out_idx_buf_opus_int16_p_0()] = pcm;
}

void call_driver_103_to_107 (const APIB_CALL_INPUT& ref) {
  OpusMSEncoder* enc = pool_buf_OpusMSEncoder_p[ref.in_idx_opusmsencoder_p_0()];
  opus_int16* pcm = pool_buf_opus_int16_p[ref.in_idx_buf_opus_int16_p_0()];
  const int pcm_size = pool__int[ref.in_idx__int_0()];
  const opus_int32 frame_size = pool__opus_int32[ref.in_idx__opus_int32_0()];
  const uint8_t* _t1_ = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];

  if (pcm_size == strlen((const char *)memcpy((void*)pcm, _t1_, pcm_size))) {
    const int len =
        opus_multistream_encode(enc, pcm, frame_size, out, MAX_PACKET);
    (void)len;
  }

  pool_buf_OpusMSEncoder_p[ref.out_idx_opusmsencoder_p_0()] = enc;
  pool_buf_opus_int16_p[ref.out_idx_buf_opus_int16_p_0()] = pcm;
}
