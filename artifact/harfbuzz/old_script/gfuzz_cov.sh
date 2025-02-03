# /graphfuzz/harfbuzz/gfuzz

if [ ! -f "./fuzz_exec_cov" ]; then

clang++-12 \
    -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../../harfbuzz_cov/test/ \
    -I../../harfbuzz_cov/test/fuzzing \
    -I../../harfbuzz_cov/src \
    fuzz_exec.cpp \
    -c -o fuzz_exec_cov.o -g


clang++-12 \
    -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../../harfbuzz_cov/test/ \
    -I../../harfbuzz_cov/test/fuzzing \
    -I../../harfbuzz_cov/src \
    -fsanitize=fuzzer,address \
    -fprofile-instr-generate -fcoverage-mapping \
    fuzz_exec_cov.o \
    -Wl,--as-needed -Wl,--no-undefined \
    -Wl,--start-group \
    ../../harfbuzz_cov/build/src/libharfbuzz.a \
    ../../harfbuzz_cov/build/src/libharfbuzz-subset.a \
    -pthread -lm -lgraphfuzz -lprotobuf \
    -Wl,--end-group \
    -lglib-2.0 \
    -lstdc++ \
    -o fuzz_exec_cov -g
fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
TARGET_CPP_FILE="$TARGET_BYTE_NAME.cc"
TARGET_OBJ_FILE="$TARGET_BYTE_NAME.o"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

./fuzz_write $TARGET_BYTE_FILE > $TARGET_CPP_FILE

clang++-12 \
    -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../../harfbuzz_cov/test/api \
    -I../../harfbuzz_cov/test/ \
    -I../../harfbuzz_cov/test/fuzzing \
    -I../../harfbuzz_cov/src \
    -fsanitize=address \
    $TARGET_CPP_FILE \
    -c -o $TARGET_OBJ_FILE -g

clang++-12 \
     -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../../harfbuzz_cov/test/api \
    -I../../harfbuzz_cov/test/ \
    -I../../harfbuzz_cov/test/fuzzing \
    -I../../harfbuzz_cov/src \
    -fsanitize=address \
    -fprofile-instr-generate -fcoverage-mapping \
    $TARGET_OBJ_FILE \
    -Wl,--as-needed -Wl,--no-undefined \
    -Wl,--start-group \
    ../../harfbuzz_cov/build/src/libharfbuzz.a \
    ../../harfbuzz_cov/build/src/libharfbuzz-subset.a \
    -pthread -lm \
    -Wl,--end-group \
    -lglib-2.0 \
    -lstdc++ \
    -o $TARGET_BYTE_NAME -g
    
LLVM_PROFILE_FILE="$COV_PROFILE" ./$TARGET_BYTE_NAME
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./$TARGET_BYTE_NAME -instr-profile=merged.profdata
