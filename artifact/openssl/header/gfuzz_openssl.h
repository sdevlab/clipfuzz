/* HEARDER DECL */
#include <openssl/x509.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
//#include "fuzzer.h"

#include "rand.inc"
/* ~HEARDER DECL */

#define MAX_BUFFER_SIZE 1048576

#include <string.h>

/* global variables */
unsigned char *original_p = 0x0;
/* ~global variables */

