# /graphfuzz/re2/gfuzz

if [ ! -f "./runner" ]; then

clang++-12 \
    src/runner.cpp \
    -c -o runner.o -g

clang-12 \
    src/x509.c \
    -I../../openssl_cov/fuzz \
    -I../../openssl_cov/include \
    -c -o x509.o -g

clang++-12 \
    runner.o x509.o \
    ../../openssl_cov/libssl.a \
    ../../openssl_cov/libcrypto.a \
    -I../../openssl_cov/fuzz \
    -I../../openssl_cov/include \
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
