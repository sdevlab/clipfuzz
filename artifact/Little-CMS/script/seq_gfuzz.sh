if [ ! -f "./fuzz_seq" ]; then
	./script/build_gfuzz_seq.sh
fi

INPUT_FILE=$1
INPUT_NAME="$(basename $INPUT_FILE)"
SEQ_FILE="${INPUT_NAME}.seq"

./fuzz_seq $INPUT_FILE -detect_leaks=0 > $SEQ_FILE
