#include <iostream>
#include <string>
#include <vector>

#include "pugixml.hpp"

struct ParamData {
  uint64_t byte_offset;
  uint64_t bit_offset;
  std::string type;
};

std::vector<ParamData> getRequiredParamData(
    const std::string& path, const std::vector<std::string>& requiredFields) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw std::runtime_error("Cannot open camera XML file");
  }

  pugi::xpath_node_set query_result = doc.select_nodes(
      "/AGV_COMM/TCP_FRAME[ID='6000']/SIGNAL_GROUP[SIGNAL[Name='SOC - State Of "
      "Charge']]");

  std::cout << query_result.size() << std::endl;

  return {};
}

int main(int argc, char** argv) {
  std::vector<std::string> requiredFields = {"SOC - State Of Charge"};

  const auto& param_data =
      getRequiredParamData("./data/Forbot_v1.xml", requiredFields);

  return 0;
}