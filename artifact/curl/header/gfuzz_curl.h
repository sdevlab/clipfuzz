/* HEARDER DECL */
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include "curl_fuzzer.h"
/* ~HEARDER DECL */
#define MAX_BUFFER_SIZE 1048576

/* global variables */
/* ~global variables */
int skipped = 0;
