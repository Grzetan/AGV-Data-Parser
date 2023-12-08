#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "config.h"
#include "pugixml.hpp"

struct ParamData {
  uint64_t byte_offset;
  uint64_t bit_offset;
  std::string type;
  std::string name;
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

    output.push_back({group_byte_offset + signal_byte_offset, bit_offset, type,
                      signal.node().child_value("Name")});
  }

  return output;
}

std::vector<std::string> parseBytes(const std::vector<u_char>& bytes,
                                    const std::vector<ParamData>& signals) {
  std::vector<std::string> output;

  for (const auto& signal : signals) {
    if (converters.find(signal.type) == converters.end()) {
      throw std::runtime_error("There is a missing converter");
    }

    converters[signal.type]->setOffsets(signal.byte_offset, signal.bit_offset);
    output.push_back(converters[signal.type]->getValue(bytes));
  }

  return output;
}

void writeCSVHeader(std::ofstream& output,
                    const std::vector<ParamData>& required_signals) {
  output << "ID;";
  for (const auto& sig : required_signals) {
    output << sig.name << ";";
  }
  output << std::endl;
}

std::vector<u_char> string2bytes(std::string& line) {
  line.erase(std::remove_if(line.begin(), line.end(),
                            [](unsigned char c) {
                              return !std::isprint(c) || c == '"' ||
                                     c == '\\' || c == 'x';
                            }),
             line.end());

  // Create a vector to store the resulting bytes
  std::vector<u_char> byteVector;

  // Iterate through pairs of characters and convert them to bytes
  for (int i = 0; i < line.size(); i += 2) {
    byteVector.push_back(std::stoi(line.substr(i, 2), nullptr, 16));
  }

  return byteVector;
}

void binary2CSV(const std::string& binary_path, const std::string& output_path,
                const std::vector<ParamData>& required_signals) {
  std::ifstream data(binary_path, std::ios::binary);
  std::ofstream output(output_path);

  writeCSVHeader(output, required_signals);

  std::string line;
  uint64_t id = 0;

  while (std::getline(data, line)) {
    output << id++ << ";";
    std::vector<u_char> bytes = string2bytes(line);
    for (const auto& val : parseBytes(bytes, required_signals)) {
      output << val << ";";
    }
    output << std::endl;
  }
}

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