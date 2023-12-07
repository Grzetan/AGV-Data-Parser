#include "converter.h"

class UIntConverter : public Converter {
 public:
  UIntConverter(const uint64_t& length);

  std::string getValue(std::ifstream& file) override;
};