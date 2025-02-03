# /graphfuzz/Little-CMS/gfuzz

if [ ! -f "./fuzz_exec_cov" ]; then
clang++-12 \
    fuzz_exec.cpp \
    -Wno-deprecated-register \
    -I../../Little-CMS_cov/include \
    -I../../Little-CMS_cov/src \
    -c -o fuzz_exec_cov.o -g

clang++-12 \
    fuzz_exec_cov.o \
     ../../Little-CMS_cov/src/.libs/liblcms2.a \
    -I../../Little-CMS_cov/include \
    -I../../Little-CMS_cov/src \
    -lgraphfuzz -lprotobuf \
    -fsanitize=fuzzer,address \
    -Wno-deprecated-register \
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
