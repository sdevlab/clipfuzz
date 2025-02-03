rm ossfuzz

CURL_INSTALL="/src/curl_install"
CURL_FUZZER="/src/curl-fuzzer"

CXXFLAGS="-DFUZZ_PROTOCOLS_HTTP -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -I/usr/lib/llvm-12/include/c++/v1 -stdlib=libc++"


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
        -o ossfuzz
