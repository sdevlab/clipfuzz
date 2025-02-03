#include <string.h>
#include <stdlib.h>
#include <cstdint>
#include <math.h>

extern "C" int graphfuzz_try();
extern "C" void graphfuzz_bail();

extern "C" void __attribute__((visibility ("default"))) global_init(int *argc, char ***argv) {
  
}

extern "C" void __attribute__((visibility ("default"))) shim_init() {
  // Do not use a character '}' in shim_init() using 'if', 'while', ...
  
}

extern "C" void __attribute__((visibility ("default"))) shim_finalize() {
  // Do not use a character '}' in shim_finalize() using 'if', 'while', ...
  
}

