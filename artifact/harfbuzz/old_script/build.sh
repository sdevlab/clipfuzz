REF_HEADER="gfuzz_harfbuzz.h"

# /graphfuzz/harfbuzz/gfuzz
rm schema.json fuzz_exec.cpp fuzz_write.cpp fuzz_exec fuzz_write schema.json cache.json
gfuzz gen cpp schema.yaml .

# fuzz_exec
sed -i -e '1,22d' fuzz_exec.cpp
sed -i -e '1r header/fuzzing_header.h' fuzz_exec.cpp
sed -i -e '1r header/'"$REF_HEADER" fuzz_exec.cpp
    
clang++-12 \
    -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../test/ \
    -I../test/fuzzing \
    -I../src \
    -fsanitize=fuzzer,address \
    fuzz_exec.cpp \
    -Wl,--as-needed -Wl,--no-undefined \
    -Wl,--start-group \
    ../build/src/libharfbuzz.a \
    ../build/src/libharfbuzz-subset.a \
    -pthread -lm -lgraphfuzz -lprotobuf \
    -Wl,--end-group \
    -lglib-2.0 \
    -lstdc++ \
    -o fuzz_exec -g

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
