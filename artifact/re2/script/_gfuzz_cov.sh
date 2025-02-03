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

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
TARGET_CPP_FILE="$TARGET_BYTE_NAME.cc"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

./fuzz_write $TARGET_BYTE_FILE > $TARGET_CPP_FILE

clang++-12 \
    $TARGET_CPP_FILE \
    ../../re2_cov/obj/libre2.a \
    -I../../re2_cov \
    $(pkg-config re2 --libs | sed -e 's/-lre2//') \
    -fsanitize=address \
    -fprofile-instr-generate -fcoverage-mapping \
    -o $TARGET_BYTE_NAME -g
    
LLVM_PROFILE_FILE="$COV_PROFILE" ASAN_OPTIONS=detect_leaks=0 ./$TARGET_BYTE_NAME
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./$TARGET_BYTE_NAME -instr-profile=merged.profdata
