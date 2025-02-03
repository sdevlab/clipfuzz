#define MAX_BUFFER_SIZE 1048576

#define MAX_PACKET (1500)
/* HEARDER DECL */
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "opus.h"
#include "opus_defines.h"
#include "opus_multistream.h"
#include "opus_types.h"
#include "../celt/os_support.h"
/* ~HEARDER DECL */

/* global variables */

opus_int32 nb_channels;
opus_int32 frequency;
static unsigned char out[MAX_PACKET];

int skipped;
/* ~global variables */

struct Wrapper_data_0 {
  unsigned char data[MAX_BUFFER_SIZE];
  size_t size;
};

struct Wrapper_data_1 {
  unsigned char data[256];
  size_t size;
};

struct Wrapper_int {
  int val;
};
