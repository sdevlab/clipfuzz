#!/bin/bash
# /graphfuzz/opus/gfuzz

TARGET_BYTE_FILE=$1
TARGET_BYTE_NAME=$(basename $TARGET_BYTE_FILE)
TARGET_SEQ_FILE="$TARGET_BYTE_NAME.seq"

if [ ! -f "./fuzz_print" ]; then

	N=$(python3 /graphfuzz/openssl/gfuzz/script/sub/parse_seq_len.py ./schema.json)
	python3 /graphfuzz/openssl/gfuzz/script/sub/gen_printer.py $N > fuzz_printer.cpp
	clang++-12 \
    		fuzz_printer.cpp \
    		-fsanitize=address \
		-lgraphfuzz -lprotobuf \
		-fsanitize=fuzzer,address \
    		-o fuzz_printer

fi

./fuzz_printer $TARGET_BYTE_FILE > $TARGET_SEQ_FILE
