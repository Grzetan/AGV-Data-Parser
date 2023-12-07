#pragma once
#include <map>
#include <memory>

#include "converters/converter.h"
#include "converters/uint_converter.h"

constexpr uint64_t tcp_frame_id = 6000;

std::map<std::string, std::shared_ptr<Converter>> converters = {
    std::make_pair("UInt", std::make_shared<UIntConverter>(4))

};