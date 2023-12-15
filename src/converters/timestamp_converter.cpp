#include "timestamp_converter.h"

TimestampConverter::TimestampConverter(const uint64_t& length)
    : Converter(std::move(length)){};

std::string TimestampConverter::getValue(const std::vector<u_char>& data) {
  const auto& bytes = getBytes(data);
  uint64_t value;
  std::memcpy(&value, bytes.data(), getLength());
  return std::to_string(value);
}
