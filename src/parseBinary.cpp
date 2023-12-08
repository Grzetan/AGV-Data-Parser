#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "pugixml.hpp"

struct ParamData {
  uint64_t byte_offset;
  uint64_t bit_offset;
  std::string type;
};

std::vector<ParamData> getRequiredParamData(
    const std::string& path, const std::vector<std::string>& required_fields) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw std::runtime_error("Cannot open camera XML file");
  }

  std::string query = "/AGV_COMM/TCP_FRAME[ID='" +
                      std::to_string(tcp_frame_id) + "']/SIGNAL_GROUP/SIGNAL[";
  for (int i = 0; i < required_fields.size(); i++) {
    query += "Name='" + required_fields[i] + "'";
    if (i != required_fields.size() - 1) {
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

std::vector<std::string> parseBytes(const std::vector<u_char>& bytes,
                                    const std::vector<ParamData>& signals) {
  std::vector<std::string> output;

  for (const auto& signal : signals) {
    if (converters.find(signal.type) == converters.end()) {
      std::cout << "There is no converter for type " << signal.type
                << std::endl;
      continue;
    }

    converters[signal.type]->setOffsets(signal.byte_offset, signal.bit_offset);
    output.push_back(converters[signal.type]->getValue(bytes));
  }

  return output;
}

void binary2CSV(const std::string& binary_path, const std::string& output_path,
                const std::vector<ParamData>& required_signals) {}

int main(int argc, char** argv) {
  std::vector<std::string> required_fields = {"Current segment"};

  const auto& required_signals =
      getRequiredParamData("./data/CoBotAGV_v2.xml", required_fields);

  // for (const auto& data : param_data) {
  //   std::cout << data.type << ", " << data.byte_offset << ", "
  //             << data.bit_offset << std::endl;
  // }

  binary2CSV("./data/data.csv", "output.csv", required_signals);

  return 0;
}