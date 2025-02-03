#include <iostream>
#include <fstream>
#include <vector>

#include <string>
#include "re2/re2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3 || size > 64) return 0;
  uint16_t f = (data[0] << 16) + data[1];
  RE2::Options opt;
  opt.set_log_errors(false);
  if (f & 1) opt.set_encoding(RE2::Options::EncodingLatin1);
  opt.set_posix_syntax(f & 2);
  opt.set_longest_match(f & 4);
  opt.set_literal(f & 8);
  opt.set_never_nl(f & 16);
  opt.set_dot_nl(f & 32);
  opt.set_never_capture(f & 64);
  opt.set_case_sensitive(f & 128);
  opt.set_perl_classes(f & 256);
  opt.set_word_boundary(f & 512);
  opt.set_one_line(f & 1024);
  const char *b = reinterpret_cast<const char*>(data) + 2;
  const char *e = reinterpret_cast<const char*>(data) + size;
  std::string s1(b, e);
  RE2 *re;
  re = new RE2(s1, opt);
  if (re->ok())
    RE2::FullMatch(s1, *(re));
  delete re;
  return 0;
}

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

    LLVMFuzzerTestOneInput(buffer.data(), buffer.size());

    return 0;
}
