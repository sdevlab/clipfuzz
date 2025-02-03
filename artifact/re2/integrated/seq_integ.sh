if [ ! -f "./seq_fuzz" ]; then
	clang++-12 sequence.cpp api_block.pb.cc -I.  libprotobuf-mutator/build/external.protobuf/lib/libprotobufd.a libprotobuf-mutator/build/external.protobuf/lib/libprotobufd.a -I libprotobuf-mutator/build/external.protobuf/include -Ilibprotobuf-mutator/build/external.googletest/include -std=c++14 -fsanitize=address -o seq_fuzz 
fi

API_BLOCK_N=$(grep -oP '#define API_BLOCK_N \K\d+' integrated_driver.cpp)

INPUT_FILE=$1
INPUT_NAME="$(basename $INPUT_FILE)"
SEQ_FILE="${INPUT_NAME}.seq"

./seq_fuzz $INPUT_FILE ${API_BLOCK_N} > $SEQ_FILE
