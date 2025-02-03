# /graphfuzz/opus/gfuzz

rm schema.json fuzz_exec.cpp fuzz_write.cpp
gfuzz gen cpp schema.yaml .

# fuzz_exec
sed -i -e '1,22d' fuzz_exec.cpp
sed -i -e '1r header/gfuzz_harfbuzz.h' fuzz_exec.cpp
sed -i -e '1r header/fuzzing_header.h' fuzz_exec.cpp

build_dir=/work/build

INCLUDE="-I${build_dir}/test/fuzzing/hb-shape-fuzzer.p -I${build_dir}/test/fuzzing -I${build_dir}/../../src/harfbuzz/test/fuzzing -I${build_dir}/ -I${build_dir}/../../src/harfbuzz -I${build_dir}/src -I${build_dir}/../../src/harfbuzz/src"
LIB="${build_dir}/src/libharfbuzz.a ${build_dir}/src/libharfbuzz-subset.a"


clang++-12 \
    ${INCLUDE} \
    -fsanitize=fuzzer,address \
    fuzz_exec.cpp \
    -Wl,--start-group \
    ${LIB} \
    -pthread -lgraphfuzz -lprotobuf \
    -Wl,--end-group \
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
