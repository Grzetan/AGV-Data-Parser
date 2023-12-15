#include <iostream>

#include "utils.h"

int main(int argc, char** argv) {
  std::vector<std::string> required_fields = {
      "Time stamp", "Cumulative distance left", "Cumulative distance right"};

  const auto& required_signals =
      getRequiredParamData("./data/CoBotAGV_v1.xml", required_fields);

  for (const auto& data : required_signals) {
    std::cout << data.type << ", " << data.byte_offset << ", "
              << data.bit_offset << std::endl;
  }

  binary2CSV("./data/ok.csv", "output.csv", required_signals);

  return 0;
}