#!/bin/bash
#set -e

if [ ! -f "./fuzz_driver_cov" ]; then

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


if [ ! -f "./obj/x509asn1.o" ]; then

CURL="/src/curl"
CURL_INSTALL="/src/curl_install"

INCLUDE_DIRS="""
   -I${CURL}/include \
   -I${CURL}/lib \
   -I${CURL}/src \
   -I${CURL}/tests/libtest \
   -DCURL_STATICLIB -DUNITTESTS \
   -isystem ${CURL_INSTALL}/include \
"""
CFLAGS="-DUSE_GNUTLS -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping"

mkdir -p obj

clang -DHAVE_CONFIG_H \
    ${CFLAGS} \
    ${INCLUDE_DIRS} \
    -O1 -fno-omit-frame-pointer \
    -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION \
    ${CURL}/lib/vtls/x509asn1.c \
    -c -o obj/x509asn1.o

fi

PROTOFILE=api_block.proto
CPP_DRIVER=integrated_driver.cpp

CURL="/src/curl"
CURL_INSTALL="/src/curl_install"
CURL_FUZZER="/src/curl-fuzzer"

INCLUDE="-I../gfuzz/header \
	-I${CURL}/tests/unit \
	-I${CURL}/tests/libtest \
	-I${CURL}/lib \
	-I${CURL_INSTALL}/include \
	-I${CURL_INSTALL}/utfuzzer \
	-I${CURL_FUZZER} \
	-lz -L${CURL_INSTALL}/lib \
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
    -c ${PROTO_CC} -stdlib=libc++ \
    -o ${PROTO_CC}.o

echo "Gen: ${PROTO_CC}.o"

# Gen libfuzzer-example-proto.a
rm libfuzzer-example-proto.a
llvm-ar-12 qc libfuzzer-example-proto.a ${PROTO_CC}.o
llvm-ranlib-12 libfuzzer-example-proto.a

CFLAGS="-DUSE_GNUTLS -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link"

clang++-12 -DHAVE_CONFIG_H \
	${CFLAGS} \
	${INCLUDE} \
	-O1 -fno-omit-frame-pointer \
	-gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION \
	-o ${CPP_DRIVER}.o \
	-c ${CPP_DRIVER} \
	-I${LIB_PROTO_ROOT} \
	-I${LIB_PROTO_BUILD} -stdlib=libc++ \
	-I${LIB_PROTO_BUILD}/external.protobuf/include \
	-I${LIB_PROTO_BUILD}/external.googletest/include 

echo "Gen: ${CPP_DRIVER}.o"

if grep -q "LLVMFuzzerTestOneInput" "${CURL_FUZZER}/curl_fuzzer.cc"; then
	pushd ${CURL_FUZZER}
	sed -i '/uint32_t to_u32/i\#INSERT_HERE_1' curl_fuzzer.cc
	sed -i '/extern "C" int LLVMFuzzerTestOneInput/,/#INSERT_HERE_1/!p;d' curl_fuzzer.cc
	clang++-12 -DPACKAGE_NAME=\"curl-fuzzer\" -DPACKAGE_TARNAME=\"curl-fuzzer\" -DPACKAGE_VERSION=\"-\" -DPACKAGE_STRING=\"curl-fuzzer\ -\" -DPACKAGE_BUGREPORT=\"a\ suitable\ curl\ mailing\ list:\ https://curl.se/mail/\" -DPACKAGE_URL=\"\" -DPACKAGE=\"curl-fuzzer\" -DVERSION=\"-\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DHAVE_DLFCN_H=1 -DLT_OBJDIR=\".libs/\"     -g -I/src/curl_install/include -I/src/curl_install/utfuzzer  -DFUZZ_PROTOCOLS_HTTP -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -I/usr/lib/llvm-12/include/c++/v1 -stdlib=libc++ -MT curl_fuzzer_http-curl_fuzzer.o -MD -MP -MF .deps/curl_fuzzer_http-curl_fuzzer.Tpo -c -o curl_fuzzer_http-curl_fuzzer.o `test -f 'curl_fuzzer.cc' || echo './'`curl_fuzzer.cc
	popd
fi

CXXFLAGS="-DFUZZ_PROTOCOLS_HTTP -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping -stdlib=libc++"

${CURL}/libtool --tag=CC   --mode=link  \
    clang++ \
        ${CXXFLAGS} \
        ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer.o \
        ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_tlv.o \
        ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_callback.o \
        ${CURL_INSTALL}/lib/libcurl.la \
	${CURL}/src/libcurltool.la \
	-L${CURL_INSTALL}/lib \
        -fsanitize=fuzzer  -lpthread -lm \
	-lnghttp2 -lssl -lcrypto -lssl -lcrypto -lz   \
	-lpthread -lm \
        obj/x509asn1.o \
        ${CPP_DRIVER}.o \
        ${LIB_PROTO_BUILD}/src/libfuzzer/libprotobuf-mutator-libfuzzer.a \
        ${LIB_PROTO_BUILD}/src/libprotobuf-mutator.a -Xlinker --start-group \
        ${LIB_PROTO_BUILD}/external.protobuf/lib/libprotobufd.a \
        -Xlinker --end-group \
        libfuzzer-example-proto.a \
        -o fuzz_driver_cov
echo "Gen: fuzz_driver_cov"

chmod +x fuzz_driver_cov

fi

if [ $# -eq 0 ]; then
    echo "Usage: $0 [byte-file]"
    exit 1
fi

INPUT_FILE=$1
COV_PROFILE="$(basename $INPUT_FILE).profraw"
ASAN_OPTIONS=detect_leaks=0 LLVM_PROFILE_FILE="$COV_PROFILE" ASAN_OPTIONS=detect_leaks=0 ./fuzz_driver_cov $1 -detect_leaks=0

#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_driver_cov -instr-profile=merged.profdata 
