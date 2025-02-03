#!/bin/bash

# /graphfuzz/opus/gfuzz

if [ ! -f "./runner" ]; then
#rm runner.o runner *.profraw *.profata

clang++-12 \
    -c ./src/runner.cpp \
    -o runner.o \
    -I../../re2_cov \

clang++-12 \
    runner.o \
    ../../re2_cov/obj/libre2.a \
    -fsanitize=address \
    -I../../re2_cov \
    $(pkg-config re2 --libs | sed -e 's/-lre2//') \
    -fprofile-instr-generate -fcoverage-mapping \
    -o runner -g

fi

if [ $# -eq 0 ]; then
    echo "Usage: $0 [byte-file]"
    exit 1
fi

INPUT_BYTE_FILE=$1
COV_PROFILE="$(basename $INPUT_BYTE_FILE).profraw"

LLVM_PROFILE_FILE="$COV_PROFILE" ./runner $1
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./runner -instr-profile=merged.profdata
