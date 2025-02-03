#include "hb-fuzzer.hh"

#include <hb-ot.h>
#include <string.h>

#include <stdlib.h>

#define TEST_OT_FACE_NO_MAIN 1
#include "../api/test-ot-face.c"
#undef TEST_OT_FACE_NO_MAIN

#include <stdio.h>

extern "C" int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  alloc_state = _fuzzing_alloc_state (data, size);

  //for (int i = 0; i < size; i++)
  //  printf("data[%d]: %d\n", i, data[i]);

  hb_blob_t *blob = hb_blob_create ((const char *)data, size,
				    HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *face = hb_face_create (blob, 0);
  hb_font_t *font = hb_font_create (face);
  hb_ot_font_set_funcs (font);
  hb_font_set_scale (font, 12, 12);

  unsigned num_coords = 0;
  if (size) num_coords = data[size - 1];
  //printf("num_coords(1): %u \n", num_coords);
  num_coords = hb_ot_var_get_axis_count (face) > num_coords ? num_coords : hb_ot_var_get_axis_count (face);
  //printf("num_coords(2): %u \n", num_coords);
  int *coords = (int *) calloc (num_coords, sizeof (int));
  if (size > num_coords + 1)
    for (unsigned i = 0; i < num_coords; ++i) {
      coords[i] = ((int) data[size - num_coords + i - 1] - 128) * 10;
      //printf("coords[%d]: %d \n", i, coords[i]);
    }
  hb_font_set_var_coords_normalized (font, coords, num_coords);
  free (coords);

  {
    const char text[] = "ABCDEXYZ123@_%&)*$!";
    hb_buffer_t *buffer = hb_buffer_create ();
    hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (HB_BUFFER_FLAG_VERIFY /* | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT */));
    hb_buffer_add_utf8 (buffer, text, -1, 0, -1);
    hb_buffer_guess_segment_properties (buffer);
    hb_shape (font, buffer, nullptr, 0);
    hb_buffer_destroy (buffer);
  }

  uint32_t text32[16] = {0};
  unsigned int len = sizeof (text32);
  if (size < len)
    len = size;
  if (len)
    memcpy (text32, data + size - len, len);

  //for (int i = 0; i < 16; i++)
	  //printf("text32[%d]: %u\n", i, text32[i]);

  /* Misc calls on font. */
  text32[10] = test_font (font, text32[15]) % 256;

  hb_buffer_t *buffer = hb_buffer_create ();
 // hb_buffer_set_flags (buffer, (hb_buffer_flags_t) (HB_BUFFER_FLAG_VERIFY | HB_BUFFER_FLAG_PRODUCE_UNSAFE_TO_CONCAT));
  hb_buffer_add_utf32 (buffer, text32, sizeof (text32) / sizeof (text32[0]), 0, -1);
  hb_buffer_guess_segment_properties (buffer);
  hb_shape (font, buffer, nullptr, 0);
  hb_buffer_destroy (buffer);

  hb_font_destroy (font);
  hb_face_destroy (face);
  hb_blob_destroy (blob);
  return 0;
}

#include <iostream>
#include <fstream>
#include <vector>

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
