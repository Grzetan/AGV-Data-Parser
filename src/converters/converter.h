#pragma once
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Converter {
 private:
  uint64_t byte_offset_, bit_offset_, length_;

 protected:
  std::vector<u_char> getBytes(const std::vector<u_char> &bytes);

  uint64_t getLength();

  Converter(const uint64_t &length);

 public:
  virtual std::string getValue(const std::vector<u_char> &data) = 0;

  void setOffsets(const uint64_t &byte_offset, const uint64_t &bit_offset);
};