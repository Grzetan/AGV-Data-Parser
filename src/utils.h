#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "pugixml.hpp"

struct ParamData {
  uint64_t byte_offset;
  uint64_t bit_offset;
  std::string type;
  std::string name;
};

std::vector<ParamData> getRequiredParamData(
    const std::string& path, const std::vector<std::string>& required_fields);

std::vector<std::string> parseBytes(const std::vector<u_char>& bytes,
                                    const std::vector<ParamData>& signals);

void writeCSVHeader(std::ofstream& output,
                    const std::vector<ParamData>& required_signals);

std::vector<u_char> string2bytes(std::string& line);

void binary2CSV(const std::string& binary_path, const std::string& output_path,
                const std::vector<ParamData>& required_signals);
