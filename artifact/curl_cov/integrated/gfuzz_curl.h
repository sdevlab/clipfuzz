/* HEARDER DECL */
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "curl_fuzzer.h"
/* ~HEARDER DECL */
#define TEST_INPUT_MAX_SIZE 10000

/* global variables */
FUZZ_DATA fuzz;
/* ~global variables */
int skipped = 0;
