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

  std::string query = "/AGV_COMM/TCP_FRAME[ID='6000']/SIGNAL_GROUP/SIGNAL[";
  for (int i = 0; i < requiredFields.size(); i++) {
    query += "Name='" + requiredFields[i] + "'";
    if (i != requiredFields.size() - 1) {
      query += " or ";
    }
  }
  query += "]";

  pugi::xpath_node_set query_result = doc.select_nodes(query.c_str());

  std::vector<ParamData> output;

  for (const auto& signal : query_result) {
    std::string type = signal.node().child_value("VAR_TYPE");
    uint64_t bit_offset = std::stol(signal.node().child_value("BIT_OFFSET"));
    uint64_t signal_byte_offset =
        std::stol(signal.node().child_value("BYTE_OFFSET"));

    uint64_t group_byte_offset =
        std::stol(signal.node().parent().child_value("OFFSET"));

    output.push_back(
        {group_byte_offset + signal_byte_offset, bit_offset, type});
  }

  return output;
}

int main(int argc, char** argv) {
  std::vector<std::string> requiredFields = {
      "SOC - State Of Charge", "Left drive activate - manual permission"};

  const auto& param_data =
      getRequiredParamData("./data/Forbot_v1.xml", requiredFields);

  for (const auto& data : param_data) {
    std::cout << data.type << ", " << data.byte_offset << ", "
              << data.bit_offset << std::endl;
  }

  return 0;
}