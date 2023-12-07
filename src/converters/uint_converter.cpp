#include "uint_converter.h"

UIntConverter::UIntConverter(const uint64_t& length)
    : Converter(std::move(length)){};

std::string UIntConverter::getValue(std::ifstream& file) {
  const auto& bytes = getBytes(file);
  uint32_t value;
  std::memcpy(&value, bytes.data(), getLength());

  return std::to_string(value);
}
