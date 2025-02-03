if [ ! -e "runner" ]; then 
    cp /out/opus_multistream_encode_fuzzer_cov  ./runner
fi

if [ $# -eq 0 ]; then
  echo "Usage: $0 SEED"
  exit 1
fi

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
COV_PROFILE="$TARGET_BYTE_NAME.profraw"

LLVM_PROFILE_FILE="$COV_PROFILE" ./runner $TARGET_BYTE_FILE
#llvm-profdata-12 merge -sparse *.profraw -o merged.profdata
#llvm-cov-12 report ./runner -instr-profile=merged.profdata -ignore-filename-regex=runner.cpp
