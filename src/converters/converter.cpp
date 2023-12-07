#include "converter.h"

Converter::Converter(const uint64_t &byte_offset, const uint64_t &bit_offset,
                     const uint64_t &length)
    : byte_offset_(std::move(byte_offset)), bit_offset_(std::move(bit_offset)),
      length_(std::move(length)) {}