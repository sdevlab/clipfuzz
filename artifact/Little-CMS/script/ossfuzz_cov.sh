# /graphfuzz/Little-CMS/gfuzz

if [ ! -f "./runner" ]; then

clang++-12 \
    -Wno-deprecated-register \
    src/runner.cpp \
    -I../../Little-CMS_cov/include \
    -I../../Little-CMS_cov/src \
    -c -o runner.o -g

clang++-12 \
    -Wno-deprecated-register \
    runner.o \
     ../../Little-CMS_cov/src/.libs/liblcms2.a \
    -I../../Little-CMS_cov/include \
    -I../../Little-CMS_cov/src \
    -lgraphfuzz -lprotobuf \
    -fsanitize=address \
    -fprofile-instr-generate -fcoverage-mapping \
    -o runner -g
fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

LLVM_PROFILE_FILE="$COV_PROFILE" ./runner $TARGET_BYTE_FILE
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./runner -instr-profile=merged.profdata
