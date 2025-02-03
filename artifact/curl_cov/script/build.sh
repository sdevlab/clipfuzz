REF_HEADER="gfuzz_curl.h"

# /graphfuzz/lcms/gfuzz
rm schema.json fuzz_exec.cpp fuzz_write.cpp
gfuzz gen cpp schema.yaml .

# fuzz_exec
sed -i -e '1,22d' fuzz_exec.cpp
sed -i -e '1r header/fuzzing_header.h' fuzz_exec.cpp
sed -i -e '1r header/'"$REF_HEADER" fuzz_exec.cpp

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
        -lgraphfuzz -lprotobuf \
        fuzz_exec.cpp \
	-o fuzz_exec

# fuzz_write
sed -i '/'"$REF_HEADER"'/d' fuzz_write.cpp

# add global variables and functions
sed -i "/std::cout << \"int main() {\" << std::endl;/i\#INSERT_HERE_1" fuzz_write.cpp
sed -i "/std::cout << \"int main() {\" << std::endl;/i\#INSERT_HERE_2" fuzz_write.cpp

sed -i'' -r -e "/#INSERT_HERE_1/i\\ \ \ \ std::cout << R\"(" fuzz_write.cpp
sed -i -e '/#INSERT_HERE_1/r ./header/'"$REF_HEADER" fuzz_write.cpp
sed -i'' -r -e "/#INSERT_HERE_2/i\)\";" fuzz_write.cpp

sed -i "/#INSERT_HERE_1/d" fuzz_write.cpp
sed -i "/#INSERT_HERE_2/d" fuzz_write.cpp

# add init() into main
sed -n -e '/shim_init/,/\}/p' ./header/fuzzing_header.h > .shim_init_body
sed -i '1d' .shim_init_body

sed -i "/std::cout << \"int main() {\" << std::endl;/a\#INSERT_HERE_2" fuzz_write.cpp
sed -i "/std::cout << \"int main() {\" << std::endl;/a\#INSERT_HERE_1" fuzz_write.cpp

sed -i'' -r -e "/#INSERT_HERE_1/i\\ \ \ \ std::cout << R\"(" fuzz_write.cpp
sed -i "/#INSERT_HERE_1/r .shim_init_body" fuzz_write.cpp
sed -i'' -r -e "/#INSERT_HERE_2/i\)\";" fuzz_write.cpp

sed -i "/#INSERT_HERE_1/d" fuzz_write.cpp
sed -i "/#INSERT_HERE_2/d" fuzz_write.cpp

# add and finalize() into main
sed -n -e '/shim_finalize/,/\}/p' ./header/fuzzing_header.h > .shim_finalize_body
sed -i '1d' .shim_finalize_body

sed -i "/std::cout << \"}\" << std::endl;/i\#INSERT_HERE_1" fuzz_write.cpp
sed -i "/std::cout << \"}\" << std::endl;/i\#INSERT_HERE_2" fuzz_write.cpp

sed -i'' -r -e "/#INSERT_HERE_1/i\\ \ \ \ std::cout << R\"(" fuzz_write.cpp
sed -i "/#INSERT_HERE_1/r .shim_finalize_body" fuzz_write.cpp
sed -i'' -r -e "/#INSERT_HERE_2/i\)\";" fuzz_write.cpp

sed -i "/#INSERT_HERE_1/d" fuzz_write.cpp
sed -i "/#INSERT_HERE_2/d" fuzz_write.cpp

sed -i "s/return;/return 0;/g" fuzz_write.cpp
clang++-12 \
    fuzz_write.cpp \
    -I. \
    -I../include \
    -lgraphfuzz -lprotobuf \
    -fsanitize=fuzzer,address \
    -o fuzz_write -g
