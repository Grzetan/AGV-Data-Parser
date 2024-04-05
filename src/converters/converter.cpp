#include "converter.h"

#include <iomanip>

Converter::Converter(const uint64_t &length) : length_(std::move(length)) {}

std::vector<u_char> Converter::getBytes(const std::vector<u_char> &bytes) {
  if (bytes.size() < byte_offset_ + length_) {
    return {};
  }

  std::vector<u_char> data(length_);

  std::copy(bytes.begin() + byte_offset_,
            bytes.begin() + byte_offset_ + length_, data.begin());

  // Fix endianess
  // std::reverse(data.begin(), data.end());

  return data;
}

uint64_t Converter::getLength() { return length_; }

void Converter::setOffsets(const uint64_t &byte_offset,
                           const uint64_t &bit_offset) {
  byte_offset_ = std::move(byte_offset);
  bit_offset_ = std::move(bit_offset);
}
