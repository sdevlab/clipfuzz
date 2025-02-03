#include "gfuzz_harfbuzz.h"

#define MAX_API_SEQ_LEN 1
#define OBJ_BANK_SIZE 1
#define PRIMITIVE_BANK_SIZE 1
#define API_BLOCK_N 21

#include "api_block.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "port/protobuf.h"
#include "src/libfuzzer/libfuzzer_macro.h"

#include <stdio.h>

int check_validity (const FUZZER_BYTES& fuzzer_bytes);
FUZZER_BYTES bound_bank_index (FUZZER_BYTES fuzzer_bytes);

hb_buffer_flags_t to_HB_BUFFER_FLAGS_T (HB_BUFFER_FLAGS_T val);
hb_memory_mode_t to_HB_MEMORY_MODE_T (HB_MEMORY_MODE_T val);


hb_blob_t * bank_hb_blob_t_p[OBJ_BANK_SIZE];
hb_buffer_flags_t bank_hb_buffer_flags_t[OBJ_BANK_SIZE];
hb_buffer_t * bank_hb_buffer_t_p[OBJ_BANK_SIZE];
hb_face_t * bank_hb_face_t_p[OBJ_BANK_SIZE];
hb_font_t * bank_hb_font_t_p[OBJ_BANK_SIZE];
hb_memory_mode_t bank_hb_memory_mode_t[OBJ_BANK_SIZE];
int bank_int[PRIMITIVE_BANK_SIZE];
size_t bank_size_t[OBJ_BANK_SIZE];
unsigned bank_unsigned[OBJ_BANK_SIZE];
const char * bank_buf_const_char_p[PRIMITIVE_BANK_SIZE];
const uint8_t * bank_buf_const_uint8_t_p[PRIMITIVE_BANK_SIZE];
int * bank_buf_int_p[OBJ_BANK_SIZE];
uint32_t * bank_buf_uint32_t_p[OBJ_BANK_SIZE];

void call_api_block_line_16_17 (const APIB_CALL_INPUT& ref);
void call_api_block_line_18 (const APIB_CALL_INPUT& ref);
void call_api_block_line_19 (const APIB_CALL_INPUT& ref);
void call_api_block_line_20 (const APIB_CALL_INPUT& ref);
void call_api_block_line_21 (const APIB_CALL_INPUT& ref);
void call_api_block_line_23_to_31 (const APIB_CALL_INPUT& ref);
void call_api_block_line_34_to_40 (const APIB_CALL_INPUT& ref);
void call_api_block_line_43_to_58 (const APIB_CALL_INPUT& ref);
void call_api_block_line_60 (const APIB_CALL_INPUT& ref);
void call_api_block_line_61 (const APIB_CALL_INPUT& ref);
void call_api_block_line_62 (const APIB_CALL_INPUT& ref);
void call_api_block_line_25 (const APIB_CALL_INPUT& ref);
void call_api_block_line_30 (const APIB_CALL_INPUT& ref);
void call_api_block_line_35 (const APIB_CALL_INPUT& ref);
void call_api_block_line_36 (const APIB_CALL_INPUT& ref);
void call_api_block_line_37 (const APIB_CALL_INPUT& ref);
void call_api_block_line_38 (const APIB_CALL_INPUT& ref);
void call_api_block_line_39 (const APIB_CALL_INPUT& ref);
void call_api_block_line_40 (const APIB_CALL_INPUT& ref);
void call_api_block_line_55 (const APIB_CALL_INPUT& ref);
void call_api_block_line_56 (const APIB_CALL_INPUT& ref);

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZER_BYTES& fuzzer_bytes) {
  printf("START! \n");

  if (check_validity(fuzzer_bytes)) 
    return;

  FUZZER_BYTES serialized_bytes = bound_bank_index(fuzzer_bytes); 

  for (int i = 0; i < OBJ_BANK_SIZE; i++) {
    bank_hb_buffer_flags_t[i] = to_HB_BUFFER_FLAGS_T(serialized_bytes.bank_init_values().hb_buffer_flags_t(i));
    bank_hb_memory_mode_t[i] = to_HB_MEMORY_MODE_T(serialized_bytes.bank_init_values().hb_memory_mode_t(i));
    bank_int[i] = serialized_bytes.bank_init_values()._int(i).val();
    bank_unsigned[i] = serialized_bytes.bank_init_values()._unsigned(i).val();

    std::string buf = serialized_bytes.bank_init_values().buf_const_uint8_t_p(i).val();
    bank_buf_const_uint8_t_p[i] = (uint8_t *)malloc(buf.length());
    std::memcpy((void*)bank_buf_const_uint8_t_p[i], buf.data(), buf.size());
    bank_size_t[i] = buf.length();
    // //

    buf = serialized_bytes.bank_init_values().buf_const_char_p(i).val();
    bank_buf_const_char_p[i] = (const char *)malloc(buf.length());
    std::memcpy((void*)bank_buf_const_char_p[i], buf.data(), buf.size());

    buf = serialized_bytes.bank_init_values().buf_int_p(i).val();
    bank_buf_int_p[i] = (int *)malloc(buf.length());
    std::memcpy((void*)bank_buf_int_p[i], buf.data(), buf.size());

    buf = serialized_bytes.bank_init_values().buf_uint32_t_p(i).val();
    bank_buf_uint32_t_p[i] = (uint32_t *)malloc(buf.length());
    std::memcpy((void*)bank_buf_uint32_t_p[i], buf.data(), buf.size());
  }

  for (int i = 0; i < serialized_bytes.api_block_call_seq_size(); i++) {
    uint32_t api_block_call_num  = serialized_bytes.api_block_call_seq(i).api_block_call_num();
    const APIB_CALL_INPUT& api_block_call_input = serialized_bytes.api_block_call_seq(i).api_block_call_input();

    switch(api_block_call_num) {
    case 0:
            call_api_block_line_16_17(api_block_call_input);
            break;
    case 1:
            call_api_block_line_18(api_block_call_input);
            break;
    case 2:
            call_api_block_line_19(api_block_call_input);
            break;
    case 3:
            call_api_block_line_20(api_block_call_input);
            break;
    case 4:
            call_api_block_line_21(api_block_call_input);
            break;
    case 5:
            call_api_block_line_23_to_31(api_block_call_input);
            break;
    case 6:
            call_api_block_line_34_to_40(api_block_call_input);
            break;
    case 7:
            call_api_block_line_43_to_58(api_block_call_input);
            break;
    case 8:
            call_api_block_line_60(api_block_call_input);
            break;
    case 9:
            call_api_block_line_61(api_block_call_input);
            break;
    case 10:
            call_api_block_line_62(api_block_call_input);
            break;
    case 11:
            call_api_block_line_25(api_block_call_input);
            break;
    case 12:
            call_api_block_line_30(api_block_call_input);
            break;
    case 13:
            call_api_block_line_35(api_block_call_input);
            break;
    case 14:
            call_api_block_line_36(api_block_call_input);
            break;
    case 15:
            call_api_block_line_37(api_block_call_input);
            break;
    case 16:
            call_api_block_line_38(api_block_call_input);
            break;
    case 17:
            call_api_block_line_39(api_block_call_input);
            break;
    case 18:
            call_api_block_line_40(api_block_call_input);
            break;
    case 19:
            call_api_block_line_55(api_block_call_input);
            break;
    case 20:
            call_api_block_line_56(api_block_call_input);
            break;
    };
  }
}

hb_buffer_flags_t to_HB_BUFFER_FLAGS_T (HB_BUFFER_FLAGS_T val) {
  switch(val) {
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
  return HB_BUFFER_FLAG_DEFAULT;
}

hb_memory_mode_t to_HB_MEMORY_MODE_T (HB_MEMORY_MODE_T val) {
  switch(val) {
  case val_HB_MEMORY_MODE_DUPLICATE: return HB_MEMORY_MODE_DUPLICATE;
  case val_HB_MEMORY_MODE_READONLY : return HB_MEMORY_MODE_READONLY;
  case val_HB_MEMORY_MODE_WRITABLE: return HB_MEMORY_MODE_WRITABLE;
  case val_HB_MEMORY_MODE_READONLY_MAY_MAKE_WRITABLE: return HB_MEMORY_MODE_READONLY_MAY_MAKE_WRITABLE;
  }
  return HB_MEMORY_MODE_DUPLICATE;
}


int check_validity (const FUZZER_BYTES& fuzzer_bytes) {
  if (fuzzer_bytes.bank_init_values().hb_buffer_flags_t_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().hb_memory_mode_t_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values()._int_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  /*if (fuzzer_bytes.bank_init_values().size_size() != OBJ_BANK_SIZE) {
    return 1;
  }*/
  if (fuzzer_bytes.bank_init_values()._unsigned_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_const_char_p_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_const_uint8_t_p_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_int_p_size() != OBJ_BANK_SIZE) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_uint32_t_p_size() != OBJ_BANK_SIZE) {
    return 1;
  }

  if (fuzzer_bytes.api_block_call_seq_size() > MAX_API_SEQ_LEN) {
    return 1;
  }

  for (int i = 0; i < PRIMITIVE_BANK_SIZE; i++) {
  if (fuzzer_bytes.bank_init_values().buf_const_char_p(i).val().length() > MAX_BUFFER_SIZE ) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_const_uint8_t_p(i).val().length() > MAX_BUFFER_SIZE ) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_int_p(i).val().length() > MAX_BUFFER_SIZE ) {
    return 1;
  }
  if (fuzzer_bytes.bank_init_values().buf_uint32_t_p(i).val().length() > MAX_BUFFER_SIZE ) {
    return 1;
  }
  }
  return 0;
}

FUZZER_BYTES bound_bank_index (FUZZER_BYTES fuzzer_bytes) {


  for (int i = 0; i < fuzzer_bytes.api_block_call_seq_size(); i++) {
    fuzzer_bytes.mutable_api_block_call_seq(i)->set_api_block_call_num(fuzzer_bytes.mutable_api_block_call_seq(i)->api_block_call_num() % API_BLOCK_N);
    APIB_CALL_INPUT *api_block_call_input = fuzzer_bytes.mutable_api_block_call_seq(i)->mutable_api_block_call_input();

    api_block_call_input->set_in_idx_hb_blob_t_p_0(api_block_call_input->in_idx_hb_blob_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_hb_buffer_flags_t_0(api_block_call_input->in_idx_hb_buffer_flags_t_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_hb_buffer_t_p_0(api_block_call_input->in_idx_hb_buffer_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_hb_face_t_p_0(api_block_call_input->in_idx_hb_face_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_hb_font_t_p_0(api_block_call_input->in_idx_hb_font_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_hb_memory_mode_t_0(api_block_call_input->in_idx_hb_memory_mode_t_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_int_0(api_block_call_input->in_idx_int_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_int_1(api_block_call_input->in_idx_int_1() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_int_2(api_block_call_input->in_idx_int_2() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_int_3(api_block_call_input->in_idx_int_3() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_size_0(api_block_call_input->in_idx_size_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_unsigned_0(api_block_call_input->in_idx_unsigned_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_buf_const_char_p_0(api_block_call_input->in_idx_buf_const_char_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_buf_const_uint8_t_p_0(api_block_call_input->in_idx_buf_const_uint8_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_buf_int_p_0(api_block_call_input->in_idx_buf_int_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_in_idx_buf_uint32_t_p_0(api_block_call_input->in_idx_buf_uint32_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_hb_blob_t_p_0(api_block_call_input->out_idx_hb_blob_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_hb_buffer_flags_t_0(api_block_call_input->out_idx_hb_buffer_flags_t_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_hb_buffer_t_p_0(api_block_call_input->out_idx_hb_buffer_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_hb_face_t_p_0(api_block_call_input->out_idx_hb_face_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_hb_font_t_p_0(api_block_call_input->out_idx_hb_font_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_hb_memory_mode_t_0(api_block_call_input->out_idx_hb_memory_mode_t_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_int_0(api_block_call_input->out_idx_int_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_int_1(api_block_call_input->out_idx_int_1() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_int_2(api_block_call_input->out_idx_int_2() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_int_3(api_block_call_input->out_idx_int_3() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_size_0(api_block_call_input->out_idx_size_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_unsigned_0(api_block_call_input->out_idx_unsigned_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_buf_const_char_p_0(api_block_call_input->out_idx_buf_const_char_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_buf_const_uint8_t_p_0(api_block_call_input->out_idx_buf_const_uint8_t_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_buf_int_p_0(api_block_call_input->out_idx_buf_int_p_0() % OBJ_BANK_SIZE);
    api_block_call_input->set_out_idx_buf_uint32_t_p_0(api_block_call_input->out_idx_buf_uint32_t_p_0() % OBJ_BANK_SIZE);

  }
  return fuzzer_bytes;
}

//ENUM

void call_api_block_line_16_17 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_memory_mode_t t0 = bank_hb_memory_mode_t[ref.in_idx_hb_memory_mode_t_0()];
   const uint8_t * data = bank_buf_const_uint8_t_p[ref.in_idx_buf_const_uint8_t_p_0()];
   size_t size = bank_size_t[ref.in_idx_size_0()];


  /* Code */

  hb_blob_t *blob = hb_blob_create ((const char *)data, size,
				    HB_MEMORY_MODE_READONLY, nullptr, nullptr);

  /* Outputs */
   bank_hb_memory_mode_t[ref.out_idx_hb_memory_mode_t_0()] = t0;
   bank_hb_blob_t_p[ref.out_idx_hb_blob_t_p_0()] = blob;
   bank_buf_const_uint8_t_p[ref.out_idx_buf_const_uint8_t_p_0()] = data;
}


void call_api_block_line_18 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_blob_t * blob = bank_hb_blob_t_p[ref.in_idx_hb_blob_t_p_0()];


  /* Code */

  hb_face_t *face = hb_face_create (blob, 0);

  /* Outputs */
   bank_hb_blob_t_p[ref.out_idx_hb_blob_t_p_0()] = blob;
   bank_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
}


void call_api_block_line_19 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_face_t * face = bank_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];


  /* Code */

  hb_font_t *font = hb_font_create (face);

  /* Outputs */
   bank_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
}


void call_api_block_line_20 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];


  /* Code */

  hb_ot_font_set_funcs (font);

  /* Outputs */
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
}


void call_api_block_line_21 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
  int t1 = bank_int[ref.in_idx_int_0()];
  int t2 = bank_int[ref.in_idx_int_1()];


  /* Code */

  hb_font_set_scale (font, 12, 12);

  /* Outputs */
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
   bank_int[ref.out_idx_int_0()] = t1;
   bank_int[ref.out_idx_int_1()] = t2;
}


void call_api_block_line_23_to_31 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_face_t * face = bank_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
   const uint8_t * data = bank_buf_const_uint8_t_p[ref.in_idx_buf_const_uint8_t_p_0()];
   size_t size = bank_size_t[ref.in_idx_size_0()];


  /* Code */

  unsigned num_coords = 0;
  if (size) num_coords = data[size - 1];
  num_coords = hb_ot_var_get_axis_count (face) > num_coords ? num_coords : hb_ot_var_get_axis_count (face);
  int *coords = (int *) calloc (num_coords, sizeof (int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i)
      coords[i] = ((int) data[size - num_coords + i - 1] - 128) * 10;
  hb_font_set_var_coords_normalized (font, coords, num_coords);
  free (coords);

  /* Outputs */
   bank_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
   bank_unsigned[ref.out_idx_unsigned_0()] = num_coords;
   bank_buf_const_uint8_t_p[ref.out_idx_buf_const_uint8_t_p_0()] = data;
}


void call_api_block_line_34_to_40 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
   hb_buffer_flags_t t3 = bank_hb_buffer_flags_t[ref.in_idx_hb_buffer_flags_t_0()];
   int t4 = bank_int[ref.in_idx_int_0()];
   int t5 = bank_int[ref.in_idx_int_1()];
   int t6 = bank_int[ref.in_idx_int_2()];
   int t7 = bank_int[ref.in_idx_int_3()];
   const uint8_t * data = bank_buf_const_uint8_t_p[ref.in_idx_buf_const_uint8_t_p_0()];


  /* Code */

    const char text[] = "ABCDEXYZ123@_%&)*$!";
    hb_buffer_t *buffer = hb_buffer_create ();
    hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (HB_BUFFER_FLAG_VERIFY /* | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT */));
    hb_buffer_add_utf8 (buffer, text, -1, 0, -1);
    hb_buffer_guess_segment_properties (buffer);
    hb_shape (font, buffer, nullptr, 0);
    hb_buffer_destroy (buffer);

  /* Outputs */
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
   bank_hb_buffer_flags_t[ref.out_idx_hb_buffer_flags_t_0()] = t3;
   bank_int[ref.out_idx_int_0()] = t4;
   bank_int[ref.out_idx_int_1()] = t5;
   bank_int[ref.out_idx_int_2()] = t6;
   bank_int[ref.out_idx_int_3()] = t7;
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
   bank_buf_const_uint8_t_p[ref.out_idx_buf_const_uint8_t_p_0()] = data;
}


void call_api_block_line_43_to_58 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
   hb_buffer_flags_t t3 = bank_hb_buffer_flags_t[ref.in_idx_hb_buffer_flags_t_0()];
   const uint8_t * data = bank_buf_const_uint8_t_p[ref.in_idx_buf_const_uint8_t_p_0()];
   size_t size = bank_size_t[ref.in_idx_size_0()];


  /* Code */

  uint32_t text32[16] = {0};
  unsigned int len = sizeof (text32);
  if (size < len)
    len = size;
  if (len)
    memcpy (text32, data + size - len, len);

  /* Misc calls on font. */
  text32[10] = test_font (font, text32[15]) % 256;

  hb_buffer_t *buffer = hb_buffer_create ();
 // hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (HB_BUFFER_FLAG_VERIFY | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT));
  hb_buffer_add_utf32 (buffer, text32, sizeof (text32) / sizeof (text32[0]), 0, -1);
  hb_buffer_guess_segment_properties (buffer);
  hb_shape (font, buffer, nullptr, 0);
  hb_buffer_destroy (buffer);

  /* Outputs */
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
   bank_hb_buffer_flags_t[ref.out_idx_hb_buffer_flags_t_0()] = t3;
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
   bank_buf_const_uint8_t_p[ref.out_idx_buf_const_uint8_t_p_0()] = data;
}


void call_api_block_line_60 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];


  /* Code */

  hb_font_destroy (font);

  /* Outputs */
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
}


void call_api_block_line_61 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_face_t * face = bank_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];


  /* Code */

  hb_face_destroy (face);

  /* Outputs */
   bank_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
}


void call_api_block_line_62 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_blob_t * blob = bank_hb_blob_t_p[ref.in_idx_hb_blob_t_p_0()];


  /* Code */

  hb_blob_destroy (blob);

  /* Outputs */
   bank_hb_blob_t_p[ref.out_idx_hb_blob_t_p_0()] = blob;
}


void call_api_block_line_25 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   unsigned num_coords = bank_unsigned[ref.in_idx_unsigned_0()];
   hb_face_t * face = bank_hb_face_t_p[ref.in_idx_hb_face_t_p_0()];


  /* Code */

  num_coords = hb_ot_var_get_axis_count (face) > num_coords ? num_coords : hb_ot_var_get_axis_count (face);

  /* Outputs */
   bank_unsigned[ref.out_idx_unsigned_0()] = num_coords;
   bank_hb_face_t_p[ref.out_idx_hb_face_t_p_0()] = face;
}


void call_api_block_line_30 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   unsigned num_coords = bank_unsigned[ref.in_idx_unsigned_0()];
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
   int * coords = bank_buf_int_p[ref.in_idx_buf_int_p_0()];


  /* Code */

hb_font_set_var_coords_normalized (font, coords, num_coords);

  /* Outputs */
   bank_unsigned[ref.out_idx_unsigned_0()] = num_coords;
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
   bank_buf_int_p[ref.out_idx_buf_int_p_0()] = coords;
}


void call_api_block_line_35 (const APIB_CALL_INPUT& ref) {
  /* Inputs */


  /* Code */

    hb_buffer_t *buffer = hb_buffer_create ();

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
}


void call_api_block_line_36 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];
   hb_buffer_flags_t t3 = bank_hb_buffer_flags_t[ref.in_idx_hb_buffer_flags_t_0()];


  /* Code */

    hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (HB_BUFFER_FLAG_VERIFY /* | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT */));


  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
   bank_hb_buffer_flags_t[ref.out_idx_hb_buffer_flags_t_0()] = t3;
}


void call_api_block_line_37 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];
   int t4 = bank_int[ref.in_idx_int_0()];
   int t5 = bank_int[ref.in_idx_int_1()];
   int t6 = bank_int[ref.in_idx_int_2()];
   int t7 = bank_int[ref.in_idx_int_3()];
   const char * text = bank_buf_const_char_p[ref.in_idx_buf_const_char_p_0()];


  /* Code */

    hb_buffer_add_utf8 (buffer, text, -1, 0, -1);

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
   bank_int[ref.out_idx_int_0()] = t4;
   bank_int[ref.out_idx_int_1()] = t5;
   bank_int[ref.out_idx_int_2()] = t6;
   bank_int[ref.out_idx_int_3()] = t7;
   bank_buf_const_char_p[ref.out_idx_buf_const_char_p_0()] = text;
}


void call_api_block_line_38 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];


  /* Code */


    hb_buffer_guess_segment_properties (buffer);

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
}


void call_api_block_line_39 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];
   hb_font_t * font = bank_hb_font_t_p[ref.in_idx_hb_font_t_p_0()];
   int t7 = bank_int[ref.in_idx_int_0()];


  /* Code */

    hb_shape (font, buffer, nullptr, 0);

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
   bank_hb_font_t_p[ref.out_idx_hb_font_t_p_0()] = font;
   bank_int[ref.out_idx_int_0()] = t7;
}


void call_api_block_line_40 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];


  /* Code */

    hb_buffer_destroy (buffer);

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
}


void call_api_block_line_55 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];
   int t8 = bank_int[ref.in_idx_int_0()];
   int t9 = bank_int[ref.in_idx_int_1()];
   uint32_t * text32 = bank_buf_uint32_t_p[ref.in_idx_buf_uint32_t_p_0()];


  /* Code */

  hb_buffer_add_utf32 (buffer, text32, sizeof (text32) / sizeof (text32[0]), 0, -1);

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
   bank_int[ref.out_idx_int_0()] = t8;
   bank_int[ref.out_idx_int_1()] = t9;
   bank_buf_uint32_t_p[ref.out_idx_buf_uint32_t_p_0()] = text32;
}


void call_api_block_line_56 (const APIB_CALL_INPUT& ref) {
  /* Inputs */
   hb_buffer_t * buffer = bank_hb_buffer_t_p[ref.in_idx_hb_buffer_t_p_0()];


  /* Code */

  hb_buffer_guess_segment_properties (buffer);

  /* Outputs */
   bank_hb_buffer_t_p[ref.out_idx_hb_buffer_t_p_0()] = buffer;
}
