#include "converter.h"

#include <iomanip>

Converter::Converter(const uint64_t &length) : length_(std::move(length)) {}

std::vector<u_char> Converter::getBytes(std::ifstream &file) {
  std::vector<u_char> data(length_);
  file.seekg(byte_offset_);
  file.read(reinterpret_cast<char *>(data.data()), length_);
  data.resize(file.gcount());

  for (const auto &byte : data) {
    std::cout << "0x" << std::setw(2) << std::setfill('0') << std::hex
              << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  return data;
}

uint64_t Converter::getLength() { return length_; }

void Converter::setOffsets(const uint64_t &byte_offset,
                           const uint64_t &bit_offset) {
  byte_offset_ = std::move(byte_offset);
  bit_offset_ = std::move(bit_offset);
}
