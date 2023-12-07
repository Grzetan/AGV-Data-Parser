#include "converter.h"

Converter::Converter(const uint64_t &byte_offset, const uint64_t &bit_offset,
                     const uint64_t &length)
    : byte_offset_(std::move(byte_offset)),
      bit_offset_(std::move(bit_offset)),
      length_(std::move(length)) {}

std::vector<u_char> Converter::getBytes(std::ifstream &file) {
  std::vector<u_char> data(length_);
  file.seekg(byte_offset_);
  file.read(reinterpret_cast<char *>(data.data()), length_);
  data.resize(file.gcount());
  return data;
}
