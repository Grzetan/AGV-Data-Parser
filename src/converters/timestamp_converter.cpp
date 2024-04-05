#include "timestamp_converter.h"
#include <sstream> 

TimestampConverter::TimestampConverter(const uint64_t& length)
    : Converter(std::move(length)){};

std::string TimestampConverter::getValue(const std::vector<u_char>& data) {
  const auto& bytes = getBytes(data);

  uint16_t year;
  std::memcpy(&year, bytes.data(), 2);
  uint8_t month;
  std::memcpy(&month, bytes.data() + 2, 1);
  uint8_t day;
  std::memcpy(&day, bytes.data() + 3, 1);
  uint8_t week_day;
  std::memcpy(&week_day, bytes.data() + 4, 1);
  uint8_t hour;
  std::memcpy(&hour, bytes.data() + 5, 1);
  int8_t minute;
  std::memcpy(&minute, bytes.data() + 6, 1);
  uint8_t second;
  std::memcpy(&second, bytes.data() + 7, 1);

  std::stringstream ss;
  ss << year << "-" << (int)month << "-" << (int)day << " " << (int)hour << ":" << (int)minute << ":" << (int)second;

  return ss.str();
}
