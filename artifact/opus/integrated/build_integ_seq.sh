#!/bin/bash
#set -e

CPP_DRIVER=seq_driver.cpp

if [ -f "seq_fuzz" ]; then
	exit
fi

if [ ! -f "$CPP_DRIVER" ]; then
	python3 gen_seq_driver.py integrated_driver.cpp
fi

LIB_PROTO_ROOT=./libprotobuf-mutator
LIB_PROTO_BUILD="${LIB_PROTO_ROOT}/build"

PROTOFILE=api_block.proto
#INCLUDE="-I.. $(pkg-config re2 --libs | sed -e 's/-lre2//')"
#LIB="../obj/libre2.a"

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
    -fsanitize=address \
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
    -fno-exceptions -Wall -Wstring-conversion -std=c++14 \
    -o ${CPP_DRIVER}.o \
    -Wno-unused-variable \
    -c ${CPP_DRIVER}

echo "Gen: ${CPP_DRIVER}.o"

clang++-12 \
    -Wno-unused-variable \
    -fno-exceptions -Wall -Wstring-conversion -fsanitize=address,fuzzer \
    ${CPP_DRIVER}.o -lz \
    -o seq_fuzz  libfuzzer-example-proto.a \
    ${LIB_PROTO_BUILD}/src/libfuzzer/libprotobuf-mutator-libfuzzer.a \
    ${LIB_PROTO_BUILD}/src/libprotobuf-mutator.a -Xlinker --start-group \
    ${LIB_PROTO_BUILD}/external.protobuf/lib/libprotobufd.a \
    -Xlinker --end-group

echo "Gen: seq_fuzz"

chmod +x seq_fuzz
