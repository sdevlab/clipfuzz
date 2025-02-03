# /graphfuzz/harfbuzz/gfuzz
  
CURL_INSTALL="/graphfuzz/curl_install_cov"
CURL_FUZZER="/graphfuzz/curl_fuzzer"

if [ ! -f "./runner" ]; then

clang++-12 \
    -I${CURL_INSTALL}/include \
    -I${CURL_INSTALL}/utfuzzer \
    -I${CURL_FUZZER} \
    -DFUZZ_PROTOCOLS_HTTP -g \
    ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer.o \
    ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_tlv.o \
    ${CURL_FUZZER}/curl_fuzzer_http-curl_fuzzer_callback.o \
    ${CURL_INSTALL}/lib/libcurl.a \
    ${CURL_INSTALL}/lib/libnghttp2.a \
    -lz -L ${CURL_INSTALL}/lib \
    -fprofile-instr-generate -fcoverage-mapping \
    -fsanitize=address \
    src/runner.cpp \
    -o runner -g

fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
PROFDATA_FILE="$TARGET_BYTE_NAME.profdata"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

ls $TARGET_BYTE_FILE -lh | awk '{print $5, $9}'
LLVM_PROFILE_FILE="$COV_PROFILE" ./runner $1
llvm-profdata-12 merge -sparse $COV_PROFILE -o $PROFDATA_FILE
llvm-cov-12 report ./runner -instr-profile=$PROFDATA_FILE | tail -n 1
echo ""
