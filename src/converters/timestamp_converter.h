#pragma once

#include "converter.h"

class TimestampConverter : public Converter {
 public:
  TimestampConverter(const uint64_t& length);

  std::string getValue(const std::vector<u_char>& data) override;
};