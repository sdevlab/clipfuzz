#include <iostream>
#include <fstream>
#include "api_block.pb.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <path-to-protobuf-file> <MAX_CALL_SIZE>" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    int MAX_CALL_SIZE = std::stoi(argv[2]);

    FUZZING_BYTES fuzzing_bytes;
    
    std::ifstream input(path, std::ios::in | std::ios::binary);
    if (!input) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return 1;
    }
        
    if (!fuzzing_bytes.ParseFromIstream(&input)) {
        std::cerr << "Failed to parse the Protobuf message." << std::endl;
        return 1;
    }
    
    const PRIMTIVE_POOL_INIT_VALUES& pool_init_values = fuzzing_bytes.pool_init_values();

    for (const auto& api_call : fuzzing_bytes.api_block_call_seq()) {
        std::cout << (api_call.api_block_call_num() % MAX_CALL_SIZE) << " ";
        const APIB_CALL_INPUT& input = api_call.api_block_call_input();
    }

    return 0;
}
