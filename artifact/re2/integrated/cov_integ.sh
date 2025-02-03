#!/bin/bash
#set -e

if [ ! -f "./fuzz_driver_cov" ]; then

LIB_PROTO_ROOT=./libprotobuf-mutator
LIB_PROTO_BUILD="${LIB_PROTO_ROOT}/build"

PROTOFILE=api_block.proto
CPP_DRIVER=integrated_driver.cpp
INCLUDE="-I../../re2_cov $(pkg-config re2 --libs | sed -e 's/-lre2//')"
LIB="../../re2_cov/obj/libre2.a"

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
    -fno-exceptions -Werror -Wall -Wstring-conversion -g -std=c++14 -fsanitize-coverage=0 \
    -c ${PROTO_CC} \
    -o ${PROTO_CC}.o

echo "Gen: ${PROTO_CC}.o"

# Gen libfuzzer-example-proto.a
rm libfuzzer-example-proto.a
llvm-ar-12 qc libfuzzer-example-proto.a ${PROTO_CC}.o
llvm-ranlib-12 libfuzzer-example-proto.a

# Gen libfuzzer_bin_example.cc.o
clang++-12 \
    -I${LIB_PROTO_ROOT} \
    -I${LIB_PROTO_BUILD} \
    -I${LIB_PROTO_BUILD}/external.protobuf/include \
    -I${LIB_PROTO_BUILD}/external.googletest/include \
    -fno-exceptions -Wall -Wstring-conversion -g -std=c++14 -fsanitize=fuzzer-no-link \
    ${INCLUDE} \
    -o ${CPP_DRIVER}.o \
    -c ${CPP_DRIVER}

echo "Gen: ${CPP_DRIVER}.o"

clang++-12 \
    -fno-exceptions -Wall -Wstring-conversion -g -fsanitize=fuzzer \
    -fprofile-instr-generate -fcoverage-mapping \
    ${CPP_DRIVER}.o \
    -o fuzz_driver_cov  libfuzzer-example-proto.a \
    ${LIB} \
    ${LIB_PROTO_BUILD}/src/libfuzzer/libprotobuf-mutator-libfuzzer.a \
    ${LIB_PROTO_BUILD}/src/libprotobuf-mutator.a -Xlinker --start-group \
    ${LIB_PROTO_BUILD}/external.protobuf/lib/libprotobufd.a \
    -Xlinker --end-group

echo "Gen: fuzz_driver"

chmod +x fuzz_driver_cov

fi

INPUT_FILE=$1
COV_PROFILE="$(basename $INPUT_FILE).profraw"
LLVM_PROFILE_FILE="$COV_PROFILE" ASAN_OPTIONS=detect_leaks=0 ./fuzz_driver_cov $1
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_driver_cov -instr-profile=merged.profdata
