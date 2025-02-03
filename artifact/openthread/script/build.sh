rm schema.json fuzz_exec.cpp fuzz_write.cpp
gfuzz gen cpp schema.yaml .

# fuzz_exec
sed -i -e '1,22d' fuzz_exec.cpp
sed -i -e '1r header/fuzzing_header.h' fuzz_exec.cpp
sed -i -e '1r header/gfuzz_openthread.h' fuzz_exec.cpp


THREAD_DIR=/src/openthread

clang++ \
  -Wno-unused-result \
  fuzz_exec.cpp \
  -I${THREAD_DIR}/include \
  -I${THREAD_DIR}/tests/fuzz \
  -I${THREAD_DIR}/src/core \
  ${THREAD_DIR}/build/tests/fuzz/CMakeFiles/ot-ip6-send-fuzzer.dir/fuzzer_platform.cpp.o \
  ${THREAD_DIR}/build/src/core/libopenthread-ftd.a \
  ${THREAD_DIR}/build/third_party/tcplp/libtcplp-ftd.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedtls.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedx509.a \
  ${THREAD_DIR}/build/third_party/mbedtls/repo/library/libmbedcrypto.a \
  ${THREAD_DIR}/build_unit/tests/unit/libot-test-platform.a \
  ${THREAD_DIR}/build_unit/examples/platforms/simulation/libopenthread-simulation.a \
    -lgraphfuzz -lprotobuf \
    -fsanitize=address,fuzzer \
    -o fuzz_exec

# fuzz_write
sed -i '/gfuzz_openthread.h/d' fuzz_write.cpp

# add global variables and functions
sed -i "/std::cout << \"int main() {\" << std::endl;/i\#INSERT_HERE_1" fuzz_write.cpp
sed -i "/std::cout << \"int main() {\" << std::endl;/i\#INSERT_HERE_2" fuzz_write.cpp

sed -i'' -r -e "/#INSERT_HERE_1/i\\ \ \ \ std::cout << R\"(" fuzz_write.cpp
sed -i "/#INSERT_HERE_1/r ./header/gfuzz_openthread.h" fuzz_write.cpp
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
    -lgraphfuzz -lprotobuf \
    -fsanitize=fuzzer,address \
    -o fuzz_write
