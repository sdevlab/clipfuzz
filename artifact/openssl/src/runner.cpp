#include <iostream>
#include <fstream>
#include <vector>      // For std::vector
#include <cstdint>     // For uint8_t

extern "C" int FuzzerInitialize(int argc, char **argv);

extern "C" int FuzzerTestOneInput(const uint8_t *buf, size_t len);

static int initialized = 0;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1], std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);

    if (!file.read(reinterpret_cast<char*>(buffer.data()), buffer.size())) {
        std::cerr << "Failed to read from file: " << argv[1] << std::endl;
        return 1;
    }

    if (! initialized) {
        FuzzerInitialize(argc, argv);
    }
    FuzzerTestOneInput(buffer.data(), buffer.size());

    return 0;
}
