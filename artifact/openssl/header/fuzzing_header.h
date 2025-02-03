#include <string.h>
#include <stdlib.h>
#include <cstdint>
#include <math.h>

extern "C" int graphfuzz_try();
extern "C" void graphfuzz_bail();

extern "C" void __attribute__((visibility ("default"))) global_init(int *argc, char ***argv) {
  OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
  ERR_clear_error();
  CRYPTO_free_ex_index(0, -1);
}

extern "C" void __attribute__((visibility ("default"))) shim_init() {
  
    OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);
    ERR_clear_error();
    CRYPTO_free_ex_index(0, -1);
    FuzzerSetRand();
}

extern "C" void __attribute__((visibility ("default"))) shim_finalize() {
  ERR_clear_error();
  
}

