#include "gfuzz_harfbuzz.h"

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

hb_memory_mode_t pool_hb_memory_mode_t[PRIMITIVE_POOL_SIZE];
hb_buffer_flags_t pool_hb_buffer_flags_t[PRIMITIVE_POOL_SIZE];
int* pool_buf_int_p[BUFFER_POOL_SIZE];
int pool__int[PRIMITIVE_POOL_SIZE];
unsigned pool__unsigned[PRIMITIVE_POOL_SIZE];
uint32_t* pool_buf_uint32_t_p[BUFFER_POOL_SIZE];
uint8_t* pool_buf_uint8_t_p[BUFFER_POOL_SIZE];
char* pool_buf_char_p[BUFFER_POOL_SIZE];
size_t pool__size_t[PRIMITIVE_POOL_SIZE];

hb_font_t* pool_hb_font_t_p[PRIMITIVE_POOL_SIZE];
hb_blob_t* pool_hb_blob_t_p[PRIMITIVE_POOL_SIZE];
hb_buffer_t* pool_buf_hb_buffer_t_p[BUFFER_POOL_SIZE];
hb_face_t* pool_hb_face_t_p[PRIMITIVE_POOL_SIZE];

void call_driver_16_to_17 (const APIB_CALL_INPUT& ref);
void call_driver_18 (const APIB_CALL_INPUT& ref);
void call_driver_19 (const APIB_CALL_INPUT& ref);
void call_driver_20 (const APIB_CALL_INPUT& ref);
void call_driver_21 (const APIB_CALL_INPUT& ref);
void call_driver_23_to_30 (const APIB_CALL_INPUT& ref);
void call_driver_31_to_53 (const APIB_CALL_INPUT& ref);
void call_driver_56 (const APIB_CALL_INPUT& ref);
void call_driver_57 (const APIB_CALL_INPUT& ref);
void call_driver_58 (const APIB_CALL_INPUT& ref);
void call_driver_60 (const APIB_CALL_INPUT& ref);
void call_driver_61 (const APIB_CALL_INPUT& ref);
void call_driver_62 (const APIB_CALL_INPUT& ref);
void call_driver_25 (const APIB_CALL_INPUT& ref);
void call_driver_35 (const APIB_CALL_INPUT& ref);
void call_driver_36 (const APIB_CALL_INPUT& ref);
void call_driver_37 (const APIB_CALL_INPUT& ref);
void call_driver_38 (const APIB_CALL_INPUT& ref);
void call_driver_39 (const APIB_CALL_INPUT& ref);
void call_driver_40 (const APIB_CALL_INPUT& ref);
void call_driver_55 (const APIB_CALL_INPUT& ref);
void call_driver_33_to_41 (const APIB_CALL_INPUT& ref);

hb_memory_mode_t to_hb_memory_mode_t (HB_MEMORY_MODE_T val) {
  switch (val) {
    case val_HB_MEMORY_MODE_READONLY: return HB_MEMORY_MODE_READONLY;
    case val_HB_MEMORY_MODE_WRITABLE: return HB_MEMORY_MODE_WRITABLE;
    case val_HB_MEMORY_MODE_READONLY_MAY_MAKE_WRITABLE: return HB_MEMORY_MODE_READONLY_MAY_MAKE_WRITABLE;
  }
}
hb_buffer_flags_t to_hb_buffer_flags_t (HB_BUFFER_FLAGS_T val) {
  switch (val) {
    case val_HB_BUFFER_FLAG_DEFAULT: return HB_BUFFER_FLAG_DEFAULT;
    case val_HB_BUFFER_FLAG_BOT: return HB_BUFFER_FLAG_BOT;
    case val_HB_BUFFER_FLAG_EOT: return HB_BUFFER_FLAG_EOT;
    case val_HB_BUFFER_FLAG_PRESERVE_DEFAULT_IGNORABLES: return HB_BUFFER_FLAG_PRESERVE_DEFAULT_IGNORABLES;
    case val_HB_BUFFER_FLAG_REMOVE_DEFAULT_IGNORABLES: return HB_BUFFER_FLAG_REMOVE_DEFAULT_IGNORABLES;
    case val_HB_BUFFER_FLAG_DO_NOT_INSERT_DOTTED_CIRCLE: return HB_BUFFER_FLAG_DO_NOT_INSERT_DOTTED_CIRCLE;
    case val_HB_BUFFER_FLAG_VERIFY: return HB_BUFFER_FLAG_VERIFY;
    case val_HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT: return HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT;
    case val_HB_BUFFER_FLAG_PRODUCE_SAFE_TO_INSERT_TATWEEL: return HB_BUFFER_FLAG_PRODUCE_SAFE_TO_INSERT_TATWEEL;
    case val_HB_BUFFER_FLAG_DEFINED: return HB_BUFFER_FLAG_DEFINED;
  }
}
int check_validity (const FUZZING_BYTES& fuzzing_bytes) {
  if (fuzzing_bytes.pool_init_values().hb_memory_mode_t_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().hb_buffer_flags_t_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_int_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._int_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values()._unsigned_size() != PRIMITIVE_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_uint32_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_uint8_t_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_char_p_size() != BUFFER_POOL_SIZE) { return 1; }
  if (fuzzing_bytes.pool_init_values().buf_hb_buffer_t_p_size() != BUFFER_POOL_SIZE) { return 1; }

  if (fuzzing_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) { return 1; }

  for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (fuzzing_bytes.pool_init_values().buf_int_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_uint32_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_char_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
    if (fuzzing_bytes.pool_init_values().buf_hb_buffer_t_p(i).val().length() > MAX_BUFFER_SIZE) { return 1; }
  }
  return 0;
}
FUZZING_BYTES bound_bank_index (FUZZING_BYTES fuzzing_bytes) {
  for (int i = 0; i < fuzzing_bytes.api_block_call_seq_size(); i++) {

    fuzzing_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzing_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzing_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_hb_memory_mode_t_0(api_block_call_input->in_idx_hb_memory_mode_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_hb_memory_mode_t_0(api_block_call_input->out_idx_hb_memory_mode_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_hb_buffer_flags_t_0(api_block_call_input->in_idx_hb_buffer_flags_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_hb_buffer_flags_t_0(api_block_call_input->out_idx_hb_buffer_flags_t_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_hb_face_t_p_0(api_block_call_input->in_idx_hb_face_t_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_hb_face_t_p_0(api_block_call_input->out_idx_hb_face_t_p_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_int_p_0(api_block_call_input->in_idx_buf_int_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_int_p_0(api_block_call_input->out_idx_buf_int_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__int_0(api_block_call_input->in_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_1(api_block_call_input->in_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_2(api_block_call_input->in_idx__int_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_in_idx__int_3(api_block_call_input->in_idx__int_3() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_0(api_block_call_input->out_idx__int_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_1(api_block_call_input->out_idx__int_1() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_2(api_block_call_input->out_idx__int_2() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__int_3(api_block_call_input->out_idx__int_3() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__unsigned_0(api_block_call_input->in_idx__unsigned_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__unsigned_0(api_block_call_input->out_idx__unsigned_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_hb_font_t_p_0(api_block_call_input->in_idx_hb_font_t_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_hb_font_t_p_0(api_block_call_input->out_idx_hb_font_t_p_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint32_t_p_0(api_block_call_input->in_idx_buf_uint32_t_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_uint32_t_p_0(api_block_call_input->out_idx_buf_uint32_t_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_uint8_t_p_0(api_block_call_input->in_idx_buf_uint8_t_p_0() % BUFFER_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_char_p_0(api_block_call_input->in_idx_buf_char_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_char_p_0(api_block_call_input->out_idx_buf_char_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx_hb_blob_t_p_0(api_block_call_input->in_idx_hb_blob_t_p_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx_hb_blob_t_p_0(api_block_call_input->out_idx_hb_blob_t_p_0() % OBJ_POOL_SIZE);

    api_block_call_input->set_in_idx_buf_hb_buffer_t_p_0(api_block_call_input->in_idx_buf_hb_buffer_t_p_0() % BUFFER_POOL_SIZE);
    api_block_call_input->set_out_idx_buf_hb_buffer_t_p_0(api_block_call_input->out_idx_buf_hb_buffer_t_p_0() % PRIMITIVE_POOL_SIZE);

    api_block_call_input->set_in_idx__size_t_0(api_block_call_input->in_idx__size_t_0() % PRIMITIVE_POOL_SIZE);
    api_block_call_input->set_out_idx__size_t_0(api_block_call_input->out_idx__size_t_0() % PRIMITIVE_POOL_SIZE);

  }
  return fuzzing_bytes;
}

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZING_BYTES& fuzzing_bytes) {
    update_max_api_seq_len();
    if (check_validity(fuzzing_bytes)) return;

    FUZZING_BYTES serialized_bytes = bound_bank_index(fuzzing_bytes);

    for (int i = 0; i < PRIMITIVE_POOL_SIZE; i++) {
      pool_hb_memory_mode_t[i] = to_hb_memory_mode_t(serialized_bytes.pool_init_values().hb_memory_mode_t(i));

      pool_hb_buffer_flags_t[i] = to_hb_buffer_flags_t(serialized_bytes.pool_init_values().hb_buffer_flags_t(i));

      pool__int[i] = (int)serialized_bytes.pool_init_values()._int(i).val();

      pool__unsigned[i] = (unsigned)serialized_bytes.pool_init_values()._unsigned(i).val();

    }
    alloc_state = _fuzzing_alloc_state(pool_buf_uint8_t_p[0], pool__size_t[0]);

    std::string buf;
    for (int i = 0; i < BUFFER_POOL_SIZE; i++) {
      buf = serialized_bytes.pool_init_values().buf_int_p(i).val();
      buf += '\0';
      pool_buf_int_p[i] = (int*)malloc(buf.length());
      std::memcpy((void*)pool_buf_int_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_uint32_t_p(i).val();
      buf += '\0';
      pool_buf_uint32_t_p[i] = (uint32_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint32_t_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_uint8_t_p(i).val();
      pool__size_t[i] = buf.length();
      buf += '\0';
      pool_buf_uint8_t_p[i] = (uint8_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_uint8_t_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_char_p(i).val();
      buf += '\0';
      pool_buf_char_p[i] = (char*)malloc(buf.length());
      std::memcpy((void*)pool_buf_char_p[i], buf.data(), buf.size());

      buf = serialized_bytes.pool_init_values().buf_hb_buffer_t_p(i).val();
      buf += '\0';
      pool_buf_hb_buffer_t_p[i] = (hb_buffer_t*)malloc(buf.length());
      std::memcpy((void*)pool_buf_hb_buffer_t_p[i], buf.data(), buf.size());

    }


  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {

      case 0:
        call_driver_16_to_17(api_block_call_input);
        break;

      case 1:
        call_driver_18(api_block_call_input);
        break;

      case 2:
        call_driver_19(api_block_call_input);
        break;

      case 3:
        call_driver_20(api_block_call_input);
        break;

      case 4:
        call_driver_21(api_block_call_input);
        break;

      case 5:
        call_driver_23_to_30(api_block_call_input);
        break;

      case 6:
        call_driver_31_to_53(api_block_call_input);
        break;

      case 7:
        call_driver_56(api_block_call_input);
        break;

      case 8:
        call_driver_57(api_block_call_input);
        break;

      case 9:
        call_driver_58(api_block_call_input);
        break;

      case 10:
        call_driver_60(api_block_call_input);
        break;

      case 11:
        call_driver_61(api_block_call_input);
        break;

      case 12:
        call_driver_62(api_block_call_input);
        break;

      case 13:
        call_driver_25(api_block_call_input);
        break;

      case 14:
        call_driver_35(api_block_call_input);
        break;

      case 15:
        call_driver_36(api_block_call_input);
        break;

      case 16:
        call_driver_37(api_block_call_input);
        break;

      case 17:
        call_driver_38(api_block_call_input);
        break;

      case 18:
        call_driver_39(api_block_call_input);
        break;

      case 19:
        call_driver_40(api_block_call_input);
        break;

      case 20:
        call_driver_55(api_block_call_input);
        break;

      case 21:
        call_driver_33_to_41(api_block_call_input);
        break;
    };
  }
}

void call_driver_16_to_17 (const APIB_CALL_INPUT& ref) {
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];
  hb_memory_mode_t _t0_ = pool_hb_memory_mode_t[ref.in_idx_hb_memory_mode_t_0()];

  hb_blob_t *blob = hb_blob_create ((const char *)data, size,
				    _t0_, nullptr, nullptr);

  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool_hb_memory_mode_t[ref.out_idx_hb_memory_mode_t_0()] = _t0_;
  pool_hb_blob_t_p[ref.out_idx_hb_blob_t_p_0()] = blob ;
}

void call_driver_18 (const APIB_CALL_INPUT& ref) {
  hb_blob_t* blob = pool_hb_blob_t_p[ref.in_idx_hb_blob_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

  hb_face_t *face = hb_face_create (blob, _t0_);

  pool_hb_blob_t_p[ref.out_idx_hb_blob_t_p_0()] = blob;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face ;
}

void call_driver_19 (const APIB_CALL_INPUT& ref) {
  hb_face_t* face = pool_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];

  hb_font_t *font = hb_font_create (face);

  pool_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font ;
}

void call_driver_20 (const APIB_CALL_INPUT& ref) {
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];

  hb_ot_font_set_funcs (font);

  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
}

void call_driver_21 (const APIB_CALL_INPUT& ref) {
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];
  int _t1_ = pool__int[ref.in_idx__int_1()];

  hb_font_set_scale (font, _t0_, _t1_);

  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool__int[ref.out_idx__int_1()] = _t1_;
}

void call_driver_23_to_30 (const APIB_CALL_INPUT& ref) {
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];
  hb_face_t* face = pool_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

  unsigned num_coords = _t0_;
  if (size) num_coords = data[size - 1];
  num_coords = hb_ot_var_get_axis_count (face) > num_coords ? num_coords : hb_ot_var_get_axis_count (face);
  int *coords = (int *) calloc (num_coords, sizeof (int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i)
      coords[i] = ((int) data[size - num_coords + i - 1] - 128) * 10;
  hb_font_set_var_coords_normalized (font, coords, num_coords);

  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool__unsigned[ref.out_idx__unsigned_0()] = num_coords ;
  pool_buf_int_p[ref.out_idx_buf_int_p_0()] = coords ;
}

void call_driver_31_to_53 (const APIB_CALL_INPUT& ref) {
  int* coords = pool_buf_int_p[ref.in_idx_buf_int_p_0()];
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  hb_face_t* face = pool_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];
  const uint8_t* data = pool_buf_uint8_t_p[ref.in_idx_buf_uint8_t_p_0()];
  size_t size = pool__size_t[ref.in_idx__size_t_0()];
  const char* _t0_ = pool_buf_char_p[ref.in_idx_buf_char_p_0()];
  hb_buffer_flags_t _t1_ = pool_hb_buffer_flags_t[ref.in_idx_hb_buffer_flags_t_0()];
  int _t2_ = pool__int[ref.in_idx__int_0()];
  int _t3_ = pool__int[ref.in_idx__int_1()];
  int _t4_ = pool__int[ref.in_idx__int_2()];
  int _t5_ = pool__int[ref.in_idx__int_3()];

  free (coords);

  {
    const char *text = _t0_;
    hb_buffer_t *buffer = hb_buffer_create ();
    hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (_t1_ /* | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT */));
    hb_buffer_add_utf8 (buffer, text, _t2_, _t3_, _t4_);
    hb_buffer_guess_segment_properties (buffer);
    hb_shape (font, buffer, nullptr, _t5_);
    hb_buffer_destroy (buffer);
  }

  uint32_t text32[16] = {0};
  unsigned int len = sizeof (text32);
  if (size < len)
    len = size;
  if (len)
    memcpy (text32, data + size - len, len);

  /* Misc calls on font. */
  text32[10] = test_font (font, text32[15]) % 256;

  hb_buffer_t *buffer = hb_buffer_create ();

  pool_buf_int_p[ref.out_idx_buf_int_p_0()] = coords;
  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
  pool_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
  pool__size_t[ref.out_idx__size_t_0()] = size;
  pool_hb_buffer_flags_t[ref.out_idx_hb_buffer_flags_t_0()] = _t1_;
  pool__int[ref.out_idx__int_0()] = _t2_;
  pool__int[ref.out_idx__int_1()] = _t3_;
  pool__int[ref.out_idx__int_2()] = _t4_;
  pool__int[ref.out_idx__int_3()] = _t5_;
  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer ;
  pool_buf_uint32_t_p[ref.out_idx_buf_uint32_t_p_0()] = text32 ;
}

void call_driver_56 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];

  hb_buffer_guess_segment_properties (buffer);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
}

void call_driver_57 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

  hb_shape (font, buffer, nullptr, _t0_);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
  pool__int[ref.out_idx__int_0()] = _t0_;
}

void call_driver_58 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];

  hb_buffer_destroy (buffer);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
}

void call_driver_60 (const APIB_CALL_INPUT& ref) {
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];

  hb_font_destroy (font);

  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
}

void call_driver_61 (const APIB_CALL_INPUT& ref) {
  hb_face_t* face = pool_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];

  hb_face_destroy (face);

  pool_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
}

void call_driver_62 (const APIB_CALL_INPUT& ref) {
  hb_blob_t* blob = pool_hb_blob_t_p[ref.in_idx_hb_blob_t_p_0()];

  hb_blob_destroy (blob);

  pool_hb_blob_t_p[ref.out_idx_hb_blob_t_p_0()] = blob;
}

void call_driver_25 (const APIB_CALL_INPUT& ref) {
  unsigned num_coords = pool__unsigned[ref.in_idx__unsigned_0()];
  hb_face_t* face = pool_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];

  num_coords = hb_ot_var_get_axis_count (face) > num_coords ? num_coords : hb_ot_var_get_axis_count (face);

  pool__unsigned[ref.out_idx__unsigned_0()] = num_coords;
  pool_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
}

void call_driver_35 (const APIB_CALL_INPUT& ref) {

    hb_buffer_t *buffer = hb_buffer_create ();

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer ;
}

void call_driver_36 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];
  hb_buffer_flags_t _t0_ = pool_hb_buffer_flags_t[ref.in_idx_hb_buffer_flags_t_0()];

    hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (_t0_ /* | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT */));

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
  pool_hb_buffer_flags_t[ref.out_idx_hb_buffer_flags_t_0()] = _t0_;
}

void call_driver_37 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];
  const char* text = pool_buf_char_p[ref.in_idx_buf_char_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];
  int _t1_ = pool__int[ref.in_idx__int_1()];
  int _t2_ = pool__int[ref.in_idx__int_2()];

    hb_buffer_add_utf8 (buffer, text, _t0_, _t1_, _t2_);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool__int[ref.out_idx__int_1()] = _t1_;
  pool__int[ref.out_idx__int_2()] = _t2_;
}

void call_driver_38 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];

    hb_buffer_guess_segment_properties (buffer);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
}

void call_driver_39 (const APIB_CALL_INPUT& ref) {
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];

    hb_shape (font, buffer, nullptr, _t0_);

  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
  pool__int[ref.out_idx__int_0()] = _t0_;
}

void call_driver_40 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];

    hb_buffer_destroy (buffer);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
}

void call_driver_55 (const APIB_CALL_INPUT& ref) {
  hb_buffer_t* buffer = pool_buf_hb_buffer_t_p[ref.in_idx_buf_hb_buffer_t_p_0()];
  uint32_t* text32 = pool_buf_uint32_t_p[ref.in_idx_buf_uint32_t_p_0()];
  int _t0_ = pool__int[ref.in_idx__int_0()];
  int _t1_ = pool__int[ref.in_idx__int_1()];

  hb_buffer_add_utf32 (buffer, text32, sizeof (text32) / sizeof (text32[0]), _t0_, _t1_);

  pool_buf_hb_buffer_t_p[ref.out_idx_buf_hb_buffer_t_p_0()] = buffer;
  pool_buf_uint32_t_p[ref.out_idx_buf_uint32_t_p_0()] = text32;
  pool__int[ref.out_idx__int_0()] = _t0_;
  pool__int[ref.out_idx__int_1()] = _t1_;
}

void call_driver_33_to_41 (const APIB_CALL_INPUT& ref) {
  hb_font_t* font = pool_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  const char* _t0_ = pool_buf_char_p[ref.in_idx_buf_char_p_0()];
  hb_buffer_flags_t _t1_ = pool_hb_buffer_flags_t[ref.in_idx_hb_buffer_flags_t_0()];
  int _t2_ = pool__int[ref.in_idx__int_0()];
  int _t3_ = pool__int[ref.in_idx__int_1()];
  int _t4_ = pool__int[ref.in_idx__int_2()];
  int _t5_ = pool__int[ref.in_idx__int_3()];

    const char *text = _t0_;
    hb_buffer_t *buffer = hb_buffer_create ();
    hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (_t1_ /* | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT */));
    hb_buffer_add_utf8 (buffer, text, _t2_, _t3_, _t4_);
    hb_buffer_guess_segment_properties (buffer);
    hb_shape (font, buffer, nullptr, _t5_);
    hb_buffer_destroy (buffer);

  pool_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
  pool_hb_buffer_flags_t[ref.out_idx_hb_buffer_flags_t_0()] = _t1_;
  pool__int[ref.out_idx__int_0()] = _t2_;
  pool__int[ref.out_idx__int_1()] = _t3_;
  pool__int[ref.out_idx__int_2()] = _t4_;
  pool__int[ref.out_idx__int_3()] = _t5_;
  pool_buf_char_p[ref.out_idx_buf_char_p_0()] = ( char*)text ;
}
