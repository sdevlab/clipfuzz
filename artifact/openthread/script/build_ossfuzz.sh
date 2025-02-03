#!/bin/bash

THREAD_DIR=/src/openthread

clang++ \
  ${THREAD_DIR}/tests/fuzz/ip6_send.cpp \
  -I${THREAD_DIR}/include \
  -I${THREAD_DIR}/tests/fuzz \
  -I${THREAD_DIR}/src/core \
  ${THREAD_DIR}/build/tests/fuzz/CMakeFiles/ot-ip6-send-fuzzer.dir/fuzzer_platform.cpp.o \
  ${THREAD_DIR}/build/src/core/libopenthread-ftd.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedtls.a \
  ${THREAD_DIR}/build/third_party/tcplp/libtcplp-ftd.a \
  ${THREAD_DIR}/build/src/core/libopenthread-ftd.a \
  ${THREAD_DIR}/build/third_party/tcplp/libtcplp-ftd.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedtls.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedx509.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedcrypto.a \
  ${THREAD_DIR}/build_unit/tests/unit/libot-test-platform.a \
  ${THREAD_DIR}/build_unit/examples/platforms/simulation/libopenthread-simulation.a \
    -fsanitize=address,fuzzer \
    -o ossfuzz
