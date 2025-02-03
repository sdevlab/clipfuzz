if [ -f "fuzz_seq" ]; then
	exit
fi

if [ ! -f "fuzz_seq.cpp" ]; then
	python3 script/gen_seq_driver.py schema.yaml
fi

clang++-12 \
    fuzz_seq.cpp \
    -I.. \
    -lgraphfuzz -lprotobuf \
    -fsanitize=fuzzer,address \
    -o fuzz_seq -g
