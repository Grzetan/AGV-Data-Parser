#include <iostream>

#include "utils.h"

int main(int argc, char** argv) {
  std::vector<std::string> required_fields = {
      "Time stamp", "Cumulative distance left", "Cumulative distance right",
      "ActualSpeed_L",
      "ActualSpeed_R",
      "AGV velocity active zone",
      "Front left strain gauge weight",
      "Front right strain gauge weight",
      "Rear left strain gauge weight",
      "Rear right strain gauge weight",
      "Momentary frequency of left encoder pulses",
      "Momentary frequency of right encoder pulses",
      "Cumulative distance left",
      "Cumulative distance right",
      "Momentary current consuption",
      "Battery cell voltage",
      "Momentary power consumption",
      "Momentary energy consumption",
      "Cumulative energy consumption",
      "CR Momentary current consuption",
      "CR Battery cell voltage",
      "CR Momentary power consumption",
      "CR Momentary energy consumption",
      "CR Cumulative energy consumption"};

  const auto& required_signals =
      getRequiredParamData("./data/CoBotAGV_v2.xml", required_fields);

  for (const auto& data : required_signals) {
    std::cout << data.type << ", " << data.byte_offset << ", "
              << data.bit_offset << std::endl;
  }

  binary2CSV("./data/dane.csv", "output.csv", required_signals);

  return 0;
}