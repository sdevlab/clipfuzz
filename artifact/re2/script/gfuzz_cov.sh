# /graphfuzz/re2/gfuzz

if [ ! -f "./fuzz_exec_cov" ]; then

clang++-12 \
    fuzz_exec.cpp \
    ../../re2_cov/obj/libre2.a \
    -I../../re2_cov \
    $(pkg-config re2 --libs | sed -e 's/-lre2//') \
    -lgraphfuzz -lprotobuf \
    -fsanitize=fuzzer,address \
    -fprofile-instr-generate -fcoverage-mapping \
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
