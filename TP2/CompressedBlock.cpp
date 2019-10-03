#include "CompressedBlock.h"
#include <algorithm>
#include <cmath>
#include <climits>
#include <bitset>
#include <string>
#include <vector>

CompressedBlock::CompressedBlock(std::vector<uint32_t> vec) {
    if (!vec.size()) return;
    reference = *std::min_element(vec.begin(), vec.end());
    for (uint i = 0; i < vec.size(); i++) {
        vec[i] -= reference;
    }

    uint32_t max = *std::max_element(vec.begin(), vec.end());
    bitsToRepr = (max == 0) ? 0 : ceil(log2(max));
    compressedNumbers = compressNumbers(vec);
}

bool CompressedBlock::valid() {
    return reference != 0;
}

std::string CompressedBlock::compressNumbers(const std::vector<uint32_t> vec) {
    std::string pack;
    for (uint i = 0; i < vec.size(); i++) {
        constexpr uint maxSize = sizeof(uint32_t) * CHAR_BIT;
        std::string binary = std::bitset<maxSize>(vec[i]).to_string();
        std::string importantBits = binary.substr(binary.size() - bitsToRepr);
        pack += importantBits;
    }

    // Padding: Until we don't have bytes, fill with 0s
    while (pack.size() % CHAR_BIT != 0)
        pack += '0';

    return pack;
}

void CompressedBlock::write(std::ostream &stream) {
    if (!valid()) return;
    uint32_t min = htobe32(reference);
    stream.write(reinterpret_cast<const char *>(&min), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&bitsToRepr), sizeof(uint8_t));

    for (uint y = 0; y < compressedNumbers.size(); y += CHAR_BIT) {
        std::string byte = compressedNumbers.substr(y, CHAR_BIT);
        ulong num = strtoul(byte.c_str(), NULL, 2);
        char *buffer = reinterpret_cast<char *>(&num);
        stream.write(buffer, sizeof(uint8_t));
    }
}

