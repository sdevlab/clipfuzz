#!/bin/bash

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
#TARGET_CPP_FILE="$TARGET_BYTE_NAME.cc"
#TARGET_OBJECT="$TARGET_BYTE_NAME.o"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

if [ ! -f "./fuzz_exec_cov" ]; then

clang++ \
    fuzz_exec.cpp \
    /src/openssl_cov/libssl.a \
    /src/openssl_cov/libcrypto.a \
    -I/src/openssl_cov/fuzz \
    -I/src/openssl_cov/include \
    -fsanitize=address,fuzzer \
    -fprofile-instr-generate -fcoverage-mapping \
    -I./header \
    -lgraphfuzz -lprotobuf \
    -o fuzz_exec_cov
fi

if [ $# -eq 0 ]; then
  echo "Usage: $0 SEED"
  exit 1
fi

LLVM_PROFILE_FILE="$COV_PROFILE" ./fuzz_exec_cov $TARGET_BYTE_FILE
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_exec_cov -instr-profile=merged.profdata
