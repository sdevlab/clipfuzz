# /graphfuzz/opus/gfuzz

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
#TARGET_CPP_FILE="$TARGET_BYTE_NAME.cc"
#TARGET_OBJECT="$TARGET_BYTE_NAME.o"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"


OPUS_DIR=/src/opus_cov

if [ ! -f "./fuzz_exec_cov" ]; then

clang++-12 \
    fuzz_exec.cpp \
    -Iheader \
    -I${OPUS_DIR}/include \
    -fprofile-instr-generate -fcoverage-mapping \
    -fsanitize=address \
    -c -o fuzz_exec_cov.o -g

clang++-12 \
    fuzz_exec_cov.o \
    ${OPUS_DIR}/.libs/libopus.a \
    -fsanitize=fuzzer,address \
    -lgraphfuzz -lprotobuf \
    -fprofile-instr-generate -fcoverage-mapping \
    -o fuzz_exec_cov -g

fi

if [ $# -eq 0 ]; then
  echo "Usage: $0 SEED"
  exit 1
fi


#./fuzz_write $TARGET_BYTE_FILE > $TARGET_CPP_FILE
   
ASAN_OPTIONS=detect_leaks=0 LLVM_PROFILE_FILE="$COV_PROFILE" ./fuzz_exec_cov $TARGET_BYTE_FILE
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./fuzz_exec_cov -instr-profile=merged.profdata
