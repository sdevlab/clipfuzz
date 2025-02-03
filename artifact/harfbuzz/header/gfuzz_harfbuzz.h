#include "hb-fuzzer.hh"

#include <hb-ot.h>
#include <string.h>

#include <stdlib.h>

#define TEST_OT_FACE_NO_MAIN 1
#include "../api/test-ot-face.c"
#undef TEST_OT_FACE_NO_MAIN
#define MAX_BUFFER_SIZE 1048576

struct Wrapper_data_0 {
  unsigned char data[MAX_BUFFER_SIZE];
  size_t size;
};
