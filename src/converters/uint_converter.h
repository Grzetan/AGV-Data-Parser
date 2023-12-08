#pragma once

#include "converter.h"

class UIntConverter : public Converter {
 public:
  UIntConverter(const uint64_t& length);

  std::string getValue(const std::vector<u_char>& data) override;
};