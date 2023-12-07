#include <map>
#include <memory>

#include "converters/converter.h"
#include "converters/uint_converter.h"

const std::map<std::string, std::unique_ptr<Converter>> converters = {
    {"UInt", std::make_unique<UIntConverter>(4)}

};