if [ ! -f "./seq_fuzz" ]; then
	./build_integ_seq.sh
fi

INPUT_FILE=$1
INPUT_NAME="$(basename $INPUT_FILE)"
SEQ_FILE="${INPUT_NAME}.seq"

./seq_fuzz $INPUT_FILE -detect_leaks=0 > $SEQ_FILE
