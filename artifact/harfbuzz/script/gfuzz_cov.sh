# /graphfuzz/opus/gfuzz

if [ ! -f "./fuzz_exec_cov" ]; then

rm schema.json fuzz_exec.cpp fuzz_write.cpp
gfuzz gen cpp schema.yaml .

# fuzz_exec
sed -i -e '1,22d' fuzz_exec.cpp
sed -i -e '1r header/gfuzz_harfbuzz.h' fuzz_exec.cpp
sed -i -e '1r header/fuzzing_header.h' fuzz_exec.cpp

build_dir=/work/build_cov

INCLUDE="-I${build_dir}/test/fuzzing/hb-shape-fuzzer.p -I${build_dir}/test/fuzzing -I${build_dir}/../../src/harfbuzz/test/fuzzing -I${build_dir}/ -I${build_dir}/../../src/harfbuzz -I${build_dir}/src -I${build_dir}/../../src/harfbuzz/src"
LIB="${build_dir}/src/libharfbuzz.a ${build_dir}/src/libharfbuzz-subset.a"

CXXFLAGS="-DFUZZ_PROTOCOLS_HTTP -O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping"

clang++-12 ${CXXFLAGS} \
    ${INCLUDE} \
    -fsanitize=fuzzer,address \
    fuzz_exec.cpp \
    -Wl,--start-group \
    ${LIB} \
    -pthread -lgraphfuzz -lprotobuf \
    -Wl,--end-group \
    -o fuzz_exec_cov -g

fi

if [ $# -eq 0 ]; then
    echo "Usage: $0 [byte-file]"
    exit 1
fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

ASAN_OPTIONS=detect_leaks=0 LLVM_PROFILE_FILE="$COV_PROFILE" ./fuzz_exec_cov $TARGET_BYTE_FILE
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_exec_cov -instr-profile=merged.profdata --ignore-filename-regex=fuzz_exec
