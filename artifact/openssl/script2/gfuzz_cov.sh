# /graphfuzz/re2/gfuzz

if [ ! -f "./fuzz_exec_cov" ]; then

clang++-12 \
    fuzz_exec.cpp \
    -I../../openssl_cov/fuzz \
    -I../../openssl_cov/include \
    -c -o fuzz_exec_cov.o -g


clang++-12 \
    fuzz_exec_cov.o \
    ../../openssl_cov/libssl.a \
    ../../openssl_cov/libcrypto.a \
    -I../../openssl_cov/fuzz \
    -I../../openssl_cov/include \
    -lgraphfuzz -lprotobuf \
    -fsanitize=fuzzer,address \
    -fprofile-instr-generate -fcoverage-mapping \
    -o fuzz_exec_cov -g
fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
TARGET_CPP_FILE="$TARGET_BYTE_NAME.cc"
TARGET_OBJ_FILE="$TARGET_BYTE_NAME.o"
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

./fuzz_write $TARGET_BYTE_FILE > $TARGET_CPP_FILE

clang++-12 \
    $TARGET_CPP_FILE \
    -I../../openssl_cov/fuzz \
    -I../../openssl_cov/include \
    -c -o $TARGET_OBJ_FILE -g
    
clang++-12 \
    $TARGET_OBJ_FILE \
    ../../openssl_cov/libssl.a \
    ../../openssl_cov/libcrypto.a \
    -I../../openssl_cov/fuzz \
    -I../../openssl_cov/include \
    -fsanitize=address \
    -fprofile-instr-generate -fcoverage-mapping \
    -o $TARGET_BYTE_NAME -g
    
LLVM_PROFILE_FILE="$COV_PROFILE" ./$TARGET_BYTE_NAME
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./$TARGET_BYTE_NAME -instr-profile=merged.profdata
