#!/bin/bash


if [ ! -f "./fuzz_driver_cov" ]; then

LIB_PROTO_ROOT=./libprotobuf-mutator
LIB_PROTO_BUILD="${LIB_PROTO_ROOT}/build"

#if [ ! $# -eq 3 ]; then
#    echo "USAGE: ./build PROTOFILE(.proto) CPP_DRIVER OPT"
#    exit
#fi
#PROTOFILE=$1
#CPP_DRIVER=$2
#OPT=$3

PROTOFILE=api_block.proto
CPP_DRIVER=integrated_driver.cpp

THREAD_DIR=/src/openthread

INCLUDE="-I../gfuzz/header -I${THREAD_DIR}/include -I${THREAD_DIR}/tests/fuzz -I${THREAD_DIR}/src/core"
LIB="${THREAD_DIR}/build_cov/tests/fuzz/CMakeFiles/ot-ip6-send-fuzzer.dir/fuzzer_platform.cpp.o \
  ${THREAD_DIR}/build_cov/src/core/libopenthread-ftd.a \
  ${THREAD_DIR}/build_cov/third_party/mbedtls/repo/library/libmbedtls.a \
  ${THREAD_DIR}/build_cov/third_party/tcplp/libtcplp-ftd.a \
  ${THREAD_DIR}/build_cov/third_party/mbedtls/repo/library/libmbedx509.a \
  ${THREAD_DIR}/build_cov/third_party/mbedtls/repo/library/libmbedcrypto.a \
  ${THREAD_DIR}/build_unit_cov/examples/platforms/simulation/libopenthread-simulation.a"



# Gen libfuzzer_example.pb.cc, libfuzzer_example.pb.h
PROTOC="${LIB_PROTO_BUILD}/external.protobuf/bin/protoc"
$PROTOC ${PROTOFILE}\
    --cpp_out . \
    -I $(dirname ${PROTOFILE})

# Gen protofile OBJ
PROTO_NAME=$(basename ${PROTOFILE})
PROTO_CC=$(echo ${PROTO_NAME} | sed 's/\.proto/.pb.cc/')
clang++-12  \
    -I${LIB_PROTO_ROOT} \
    -I${LIB_PROTO_BUILD} \
    -I${LIB_PROTO_BUILD}/external.protobuf/include \
    -I${LIB_PROTO_BUILD}/external.googletest/include \
    -Wno-deprecated-register \
    -fno-exceptions -Wstring-conversion -g -std=c++14 -fsanitize-coverage=0 \
    -c ${PROTO_CC} \
    -o ${PROTO_CC}.o

echo "Gen: ${PROTO_CC}.o"

# Gen libfuzzer-example-proto.a
rm libfuzzer-example-proto.a
llvm-ar-12 qc libfuzzer-example-proto.a ${PROTO_CC}.o
llvm-ranlib-12 libfuzzer-example-proto.a

#sed -i "s/return;/return 0;/g" integrated_driver.cpp

# Gen libfuzzer_bin_example.cc.o
    #-o CMakeFiles/libfuzzer_bin_example.dir/libfuzzer_bin_example.cc.o \
clang++-12 \
    -I${LIB_PROTO_ROOT} \
    -I${LIB_PROTO_BUILD} \
    -I${LIB_PROTO_BUILD}/external.protobuf/include \
    -I${LIB_PROTO_BUILD}/external.googletest/include \
    -fprofile-instr-generate -fcoverage-mapping \
    -Wno-unused-result \
    -Wno-deprecated-register \
    -fno-exceptions -Wstring-conversion -std=c++14 -fsanitize=fuzzer-no-link \
    ${INCLUDE} \
    -o ${CPP_DRIVER}.o \
    -c ${CPP_DRIVER}
    #-MD -MT examples/libfuzzer/CMakeFiles/libfuzzer_bin_example.dir/libfuzzer_bin_example.cc.o -MF CMakeFiles/libfuzzer_bin_example.dir/libfuzzer_bin_example.cc.o.d \

echo "Gen: ${CPP_DRIVER}.o"

    #CMakeFiles/libfuzzer_bin_example.dir/libfuzzer_bin_example.cc.o \
clang++-12 \
    -fno-exceptions -Werror -Wall -Wstring-conversion -fsanitize=address,fuzzer \
    -fprofile-instr-generate -fcoverage-mapping \
    ${CPP_DRIVER}.o \
    -o fuzz_driver_cov  libfuzzer-example-proto.a \
    ${LIB} -std=c++14 \
    ${LIB_PROTO_BUILD}/src/libfuzzer/libprotobuf-mutator-libfuzzer.a \
    ${LIB_PROTO_BUILD}/src/libprotobuf-mutator.a -Xlinker --start-group \
    ${LIB_PROTO_BUILD}/external.protobuf/lib/libprotobufd.a \
    -Xlinker --end-group

echo "Gen: fuzz_driver_cov"

chmod +x fuzz_driver_cov

fi

if [ $# -eq 0 ]; then
  echo "Usage: $0 SEED"
  exit 1
fi

INPUT_FILE=$1
COV_PROFILE="$(basename $INPUT_FILE).profraw"

timeout 1s sh -c "LLVM_PROFILE_FILE="$COV_PROFILE" ASAN_OPTIONS=detect_leaks=0 ./fuzz_driver_cov $1 -detect_leaks=0 -timeout=1"

#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_driver_cov -instr-profile=merged.profdata
