#include <iostream>

#include "utils.h"

int main(int argc, char** argv) {
  std::vector<std::string> required_fields = {"Current segment",
                                              "ActualSpeed_R"};

  const auto& required_signals =
      getRequiredParamData("./data/CoBotAGV_v2.xml", required_fields);

  for (const auto& data : required_signals) {
    std::cout << data.type << ", " << data.byte_offset << ", "
              << data.bit_offset << std::endl;
  }

  binary2CSV("./data/data.csv", "output.csv", required_signals);

  return 0;
}