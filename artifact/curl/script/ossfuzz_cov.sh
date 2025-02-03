# /graphfuzz/harfbuzz/gfuzz
  

CURL_INSTALL="/src/curl_install"
CURL_FUZZER="/src/curl-fuzzer"

if [ ! -f "./runner" ]; then


CXXFLAGS="-DFUZZ_PROTOCOLS_HTTP -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fprofile-instr-generate -fcoverage-mapping" 


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
        ./src/ossfuzz_driver.cpp \
        -o runner
fi

if [ $# -eq 0 ]; then
  echo "Usage: $0 SEED"
  exit 1
fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

LLVM_PROFILE_FILE="$COV_PROFILE" ./runner $TARGET_BYTE_FILE
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./runner -instr-profile=merged.profdata -ignore-filename-regex=runner.cpp
