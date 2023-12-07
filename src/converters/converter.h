#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Converter {
  uint64_t byte_offset_, bit_offset_, length_;

  Converter(const uint64_t &byte_offset, const uint64_t &bit_offset,
            const uint64_t &length);

  std::vector<u_char> getBytes(std::ifstream &file);

  virtual std::string getValue(std::ifstream &file) = 0;
};