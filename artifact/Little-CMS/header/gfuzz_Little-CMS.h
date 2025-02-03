#define MAX_BUFFER_SIZE 1048576

/* HEARDER DECL */
#include <stdint.h>

#include "lcms2.h"
#include "lcms2_internal.h"
/* ~HEARDER DECL */

/* FUZZ_WRITE */
#include "string.h"
#include "stdlib.h"
/* ~FUZZ_WRITE */

struct Wrapper_cmsColorSpaceSignature {
  cmsColorSpaceSignature val;
};

struct Wrapper_cmsUInt32Number {
  cmsUInt32Number val;
};
