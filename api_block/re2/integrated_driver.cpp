#include "gfuzz_re2.h"

//#define MAX_API_SEQ_LEN 26
#define OBJ_POOL_SIZE 0
#define PRIMITIVE_POOL_SIZE 0
#define BUFFER_POOL_SIZE 0
#define API_BLOCK_N 19
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


uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
RE2::Options::Encoding pool_RE2__Options__Encoding[PRIMITIVE_POOL_SIZE];
std::string pool_buf_std__string[BUFFER_POOL_SIZE];
uint16_t pool__uint16_t[PRIMITIVE_POOL_SIZE];
RE2::Options pool_RE2__Options[PRIMITIVE_POOL_SIZE];
bool pool__bool[PRIMITIVE_POOL_SIZE];
size_t pool__size_t[PRIMITIVE_POOL_SIZE];
RE2* pool_RE2_p[PRIMITIVE_POOL_SIZE];

void call_driver_7_to_10 (const APIB_CALL_INPUT& ref);
void call_driver_11_to_12 (const APIB_CALL_INPUT& ref);
void call_driver_13 (const APIB_CALL_INPUT& ref);
void call_driver_14 (const APIB_CALL_INPUT& ref);
void call_driver_15 (const APIB_CALL_INPUT& ref);
void call_driver_16 (const APIB_CALL_INPUT& ref);
void call_driver_17 (const APIB_CALL_INPUT& ref);
void call_driver_18 (const APIB_CALL_INPUT& ref);
void call_driver_19 (const APIB_CALL_INPUT& ref);
void call_driver_20 (const APIB_CALL_INPUT& ref);
void call_driver_21 (const APIB_CALL_INPUT& ref);
void call_driver_22_to_26 (const APIB_CALL_INPUT& ref);
void call_driver_27_to_29 (const APIB_CALL_INPUT& ref);
void call_RE2 (const APIB_CALL_INPUT& ref);
void call_set_encoding (const APIB_CALL_INPUT& ref);
void call_ok (const APIB_CALL_INPUT& ref);
void call_FullMatch (const APIB_CALL_INPUT& ref);
void call_driver_11 (const APIB_CALL_INPUT& ref);
void call_driver_27_to_28 (const APIB_CALL_INPUT& ref);

RE2::Options::Encoding to_RE2__Options__Encoding (RE2__OPTIONS__ENCODING val) {
  switch (val) {
    case val_RE2__Options__EncodingUTF8: return RE2::Options::EncodingUTF8;
    case val_RE2__Options__EncodingLatin1: return RE2::Options::EncodingLatin1;
  }
}
int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().re2__options__encoding_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_std__string_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._uint16_t_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._bool_size() != PRIMITIVE_POOL_SIZE) { return 1; }

  if (fuzzing_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) { return 1; }

  for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (fuzzing_bytes.pool_init_values().buf_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_std__string(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
  }
  return 0;
}
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes) {
  for (int i = 0; i < fuzzing_bytes.api_block_call_seq_size(); i++) {

    fuzzing_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzing_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzing_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);

    api_block_call_input->set_in_idx_re2__options__encoding_0(api_block_call_input->in_idx_re2__options__encoding_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_re2__options__encoding_0(api_block_call_input->out_idx_re2__options__encoding_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_std__string_0(api_block_call_input->in_idx_buf_std__string_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_std__string_0(api_block_call_input->out_idx_buf_std__string_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__uint16_t_0(api_block_call_input->in_idx__uint16_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__uint16_t_0(api_block_call_input->out_idx__uint16_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_re2__options_0(api_block_call_input->in_idx_re2__options_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_re2__options_0(api_block_call_input->out_idx_re2__options_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx__bool_0(api_block_call_input->in_idx__bool_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__bool_0(api_block_call_input->out_idx__bool_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__size_t_0(api_block_call_input->in_idx__size_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__size_t_0(api_block_call_input->out_idx__size_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_re2_p_0(api_block_call_input->in_idx_re2_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_re2_p_0(api_block_call_input->out_idx_re2_p_0() % OBJ_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
      pool_RE2__Options__Encoding[i] = to_RE2__Options__Encoding(serialized_bytes.pool_init_values().re2__options__encoding(i));

      pool__uint16_t[i] = (uint16_t)serialized_bytes.pool_init_values()._uint16_t(i).val();

      pool__bool[i] = (bool)serialized_bytes.pool_init_values()._bool(i).val();

    }


    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      pool__size_t[i] = buf.length();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

      pool_buf_std__string[i] = serialized_bytes.pool_init_values().buf_std__string(i).val();

    }


  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_7_to_10(api_block_call_input);
        break;

      case 1:
        call_driver_11_to_12(api_block_call_input);
        break;

      case 2:
        call_driver_13(api_block_call_input);
        break;

      case 3:
        call_driver_14(api_block_call_input);
        break;

      case 4:
        call_driver_15(api_block_call_input);
        break;

      case 5:
        call_driver_16(api_block_call_input);
        break;

      case 6:
        call_driver_17(api_block_call_input);
        break;

      case 7:
        call_driver_18(api_block_call_input);
        break;

      case 8:
        call_driver_19(api_block_call_input);
        break;

      case 9:
        call_driver_20(api_block_call_input);
        break;

      case 10:
        call_driver_21(api_block_call_input);
        break;

      case 11:
        call_driver_22_to_26(api_block_call_input);
        break;

      case 12:
        call_driver_27_to_29(api_block_call_input);
        break;

      case 13:
        call_RE2(api_block_call_input);
        break;

      case 14:
        call_set_encoding(api_block_call_input);
        break;

      case 15:
        call_ok(api_block_call_input);
        break;

      case 16:
        call_FullMatch(api_block_call_input);
        break;

      case 17:
        call_driver_11(api_block_call_input);
        break;

      case 18:
        call_driver_27_to_28(api_block_call_input);
        break;
    };
  }
}

void call_driver_7_to_10 (const APIB_CALL_INPUT& ref) {
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];
  bool _t0_ = pool__bool[ref.in_idx__bool_0()];

  if (size < 3 || size > 64) {}//return 0;
  uint16_t f = (data[0] << 16) + data[1];
  RE2::Options opt;
  opt.set_log_errors(_t0_);

  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool__bool[ref.out_idx__bool_0()] = _t0_;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f ;
  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt ;
}

void call_driver_11_to_12 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];
  RE2::Options::Encoding _t0_ = pool_RE2__Options__Encoding[ref.in_idx_re2__options__encoding_0()];

  if (f & 1) opt.set_encoding(_t0_);
  opt.set_posix_syntax(f & 2);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
  pool_RE2__Options__Encoding[ref.out_idx_re2__options__encoding_0()] = _t0_;
}

void call_driver_13 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_longest_match(f & 4);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_14 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_literal(f & 8);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_15 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_never_nl(f & 16);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_16 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_dot_nl(f & 32);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_17 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_never_capture(f & 64);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_18 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_case_sensitive(f & 128);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_19 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_perl_classes(f & 256);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_20 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_word_boundary(f & 512);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_21 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];

  opt.set_one_line(f & 1024);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
}

void call_driver_22_to_26 (const APIB_CALL_INPUT& ref) {
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];

  const char *b = reinterpret_cast<const char*>(data) + 2;
  const char *e = reinterpret_cast<const char*>(data) + size;
  std::string s1(b, e);
  RE2 *re;
  re = new RE2(s1, opt);

  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool_buf_std__string[ref.out_idx_buf_std__string_0()] = s1 ;
  pool_RE2_p[ref.out_idx_re2_p_0()] = re ;
}

void call_driver_27_to_29 (const APIB_CALL_INPUT& ref) {
  std::string s1 = pool_buf_std__string[ref.in_idx_buf_std__string_0()];
  RE2* re = pool_RE2_p[ref.in_idx_re2_p_0()];

  if (re->ok())
    RE2::FullMatch(s1, *(re));
  delete re;

  pool_buf_std__string[ref.out_idx_buf_std__string_0()] = s1;
  pool_RE2_p[ref.out_idx_re2_p_0()] = re;
}

void call_RE2 (const APIB_CALL_INPUT& ref) {
  std::string s1 = pool_buf_std__string[ref.in_idx_buf_std__string_0()];
  RE2* re = pool_RE2_p[ref.in_idx_re2_p_0()];
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];

  re = new RE2(s1, opt);

  pool_buf_std__string[ref.out_idx_buf_std__string_0()] = s1;
  pool_RE2_p[ref.out_idx_re2_p_0()] = re;
  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
}

void call_set_encoding (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  RE2::Options::Encoding _t0_ = pool_RE2__Options__Encoding[ref.in_idx_re2__options__encoding_0()];

  opt.set_encoding(_t0_);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool_RE2__Options__Encoding[ref.out_idx_re2__options__encoding_0()] = _t0_;
}

void call_ok (const APIB_CALL_INPUT& ref) {
  RE2* re = pool_RE2_p[ref.in_idx_re2_p_0()];

  re->ok();

  pool_RE2_p[ref.out_idx_re2_p_0()] = re;
}

void call_FullMatch (const APIB_CALL_INPUT& ref) {
  std::string s1 = pool_buf_std__string[ref.in_idx_buf_std__string_0()];
  RE2* re = pool_RE2_p[ref.in_idx_re2_p_0()];

    RE2::FullMatch(s1, *(re));

  pool_buf_std__string[ref.out_idx_buf_std__string_0()] = s1;
  pool_RE2_p[ref.out_idx_re2_p_0()] = re;
}

void call_driver_11 (const APIB_CALL_INPUT& ref) {
  RE2::Options opt = pool_RE2__Options[ref.in_idx_re2__options_0()];
  uint16_t f = pool__uint16_t[ref.in_idx__uint16_t_0()];
  RE2::Options::Encoding _t0_ = pool_RE2__Options__Encoding[ref.in_idx_re2__options__encoding_0()];

  if (f & 1) opt.set_encoding(_t0_);

  pool_RE2__Options[ref.out_idx_re2__options_0()] = opt;
  pool__uint16_t[ref.out_idx__uint16_t_0()] = f;
  pool_RE2__Options__Encoding[ref.out_idx_re2__options__encoding_0()] = _t0_;
}

void call_driver_27_to_28 (const APIB_CALL_INPUT& ref) {
  std::string s1 = pool_buf_std__string[ref.in_idx_buf_std__string_0()];
  RE2* re = pool_RE2_p[ref.in_idx_re2_p_0()];

  if (re->ok())
    RE2::FullMatch(s1, *(re));

  pool_buf_std__string[ref.out_idx_buf_std__string_0()] = s1;
  pool_RE2_p[ref.out_idx_re2_p_0()] = re;
}
