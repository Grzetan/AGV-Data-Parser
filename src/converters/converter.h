#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Converter {
 private:
  uint64_t byte_offset_, bit_offset_, length_;

 protected:
  std::vector<u_char> getBytes(std::ifstream &file);

  uint64_t getLength();

  Converter(const uint64_t &length);

 public:
  virtual std::string getValue(std::ifstream &file) = 0;

  void setOffsets(const uint64_t &byte_offset, const uint64_t &bit_offset);
};