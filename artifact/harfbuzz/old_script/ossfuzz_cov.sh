#!/bin/bash
INPUT_BYTE_FILE=$1
COV_PROFILE="$(basename $INPUT_BYTE_FILE).profraw"

if [ ! -f "./runner" ]; then
rm runner.o runner *.profraw *.profdata

clang++-12 \
    -c ./src/runner.cpp \
    -o runner.o \
    -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../../harfbuzz_cov/test/ \
    -I../../harfbuzz_cov/test/fuzzing \
    -I../../harfbuzz_cov/src

clang++-12 \
    -I/usr/include/glib-2.0 \
    -I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
    -I../../harfbuzz_cov/test/api \
    -I../../harfbuzz_cov/test/ \
    -I../../harfbuzz_cov/test/fuzzing \
    -I../../harfbuzz_cov/src \
    -fsanitize=address \
    -fprofile-instr-generate -fcoverage-mapping \
    runner.o \
    -Wl,--as-needed -Wl,--no-undefined \
    -Wl,--start-group \
    ../../harfbuzz_cov/build/src/libharfbuzz.a \
    ../../harfbuzz_cov/build/src/libharfbuzz-subset.a \
    -pthread -lm \
    -Wl,--end-group \
    -lglib-2.0 \
    -lstdc++ \
    -o runner -g

fi

LLVM_PROFILE_FILE="$COV_PROFILE" ./runner "$1"
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./runner -instr-profile=merged.profdata
