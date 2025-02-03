#!/bin/bash
#set -e

LIB_PROTO_ROOT=./libprotobuf-mutator
LIB_PROTO_BUILD="${LIB_PROTO_ROOT}/build"

CFLAGS=""
CXXFLAGS=""
CC=""
CXX=""

#if [ ! $# -eq 3 ]; then
#    echo "USAGE: ./build PROTOFILE(.proto) CPP_DRIVER OPT"
#    exit
#fi
#PROTOFILE=$1
#CPP_DRIVER=$2
#OPT=$3


PROTOFILE=api_block.proto
CPP_DRIVER=integrated_driver.cpp

CURL_INSTALL="/src/curl_install"
CURL_FUZZER="/src/curl-fuzzer"

INCLUDE="\
	-I${CURL_INSTALL}/include \
	-I${CURL_INSTALL}/utfuzzer \
	-I${CURL_FUZZER} \
	-lz -L ${CURL_INSTALL}/lib \
	-DFUZZ_PROTOCOLS_HTTP"

LIB="\
	-DFUZZ_PROTOCOLS_HTTP \
	${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer.o \
	${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_tlv.o \
	${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_callback.o \
	${CURL_INSTALL}/lib/libcurl.a \
	${CURL_INSTALL}/lib/libnghttp2.a \
	${CURL_FUZZER}/libstandaloneengine.a"

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
    -Wno-deprecated-register \
    -fno-exceptions -Wstring-conversion -g -std=c++14 -fsanitize=address,fuzzer-no-link \
    ${INCLUDE} \
    -o ${CPP_DRIVER}.o \
    -c ${CPP_DRIVER}
    #-MD -MT examples/libfuzzer/CMakeFiles/libfuzzer_bin_example.dir/libfuzzer_bin_example.cc.o -MF CMakeFiles/libfuzzer_bin_example.dir/libfuzzer_bin_example.cc.o.d \

echo "Gen: ${CPP_DRIVER}.o"


CXXFLAGS="-DFUZZ_PROTOCOLS_HTTP -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link"

        #${INCLUDE} \
${CURL_FUZZER}/libtool  --tag=CXX   --mode=link  \
    clang++ \
        ${CXXFLAGS} -g \
        -I${CURL_INSTALL}/include \
        -I${CURL_INSTALL}/utfuzzer \
        -I${CURL_FUZZER} \
        ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer.o \
        ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_tlv.o \
        ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_callback.o \
        ${CURL_INSTALL}/lib/libcurl.la \
        -fsanitize=fuzzer  -lpthread -lm \
        -lgraphfuzz \
        ${CPP_DRIVER}.o \
        ${LIB_PROTO_BUILD}/src/libfuzzer/libprotobuf-mutator-libfuzzer.a \
        ${LIB_PROTO_BUILD}/src/libprotobuf-mutator.a -Xlinker --start-group \
        ${LIB_PROTO_BUILD}/external.protobuf/lib/libprotobufd.a \
        -Xlinker --end-group \
        libfuzzer-example-proto.a \
        -o fuzz_driver


echo "Gen: fuzz_driver"

chmod +x fuzz_driver
