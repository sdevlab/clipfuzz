#define TEST_INPUT_MAX_SIZE 1048576

/* HEARDER DECL */
#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <string>
#include <vector>

#include "re2/filtered_re2.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/set.h"
#include "re2/walker-inl.h"
/* ~HEARDER DECL */

/* global variables */
/* ~global variables */

struct Wrapper_data_0 {
  unsigned char data[TEST_INPUT_MAX_SIZE];
  size_t size;
};
