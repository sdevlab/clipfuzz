#!/bin/bash

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
#TARGET_CPP_FILE="$TARGET_BYTE_NAME.cc"
#TARGET_OBJECT="$TARGET_BYTE_NAME.o"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"


if [ ! -f "./fuzz_exec_cov" ]; then

THREAD_DIR=/src/openthread

clang++ \
  -Wno-unused-result \
  fuzz_exec.cpp \
  -I${THREAD_DIR}/include \
  -I${THREAD_DIR}/tests/fuzz \
  -I${THREAD_DIR}/src/core \
  ${THREAD_DIR}/build_cov/tests/fuzz/CMakeFiles/ot-ip6-send-fuzzer.dir/fuzzer_platform.cpp.o \
  ${THREAD_DIR}/build_cov/src/core/libopenthread-ftd.a \
  ${THREAD_DIR}/build_cov/third_party/tcplp/libtcplp-ftd.a \
  ${THREAD_DIR}/build_cov/third_party/mbedtls/repo/library/libmbedtls.a \
  ${THREAD_DIR}/build_cov/third_party/mbedtls/repo/library/libmbedx509.a \
  ${THREAD_DIR}/build_cov/third_party/mbedtls/repo/library/libmbedcrypto.a \
  ${THREAD_DIR}/build_unit_cov/examples/platforms/simulation/libopenthread-simulation.a \
    -lgraphfuzz -lprotobuf \
    -fprofile-instr-generate -fcoverage-mapping \
    -fsanitize=address,fuzzer \
    -o fuzz_exec_cov


fi

if [ $# -eq 0 ]; then
  echo "Usage: $0 SEED"
  exit 1
fi

LLVM_PROFILE_FILE="$COV_PROFILE" ./fuzz_exec_cov $TARGET_BYTE_FILE -timeout=1
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_exec_cov -instr-profile=merged.profdata
