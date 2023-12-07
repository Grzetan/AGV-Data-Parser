#include <iostream>
#include <string>

class Converter {
  uint64_t byte_offset_, bit_offset_, length_;

  Converter(const uint64_t &byte_offset, const uint64_t &bit_offset,
            const uint64_t &length);

  virtual std::string getValue(const std::ifstream &file) = 0;
};