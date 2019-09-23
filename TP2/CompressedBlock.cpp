#include "CompressedBlock.h"
#include <algorithm>
#include <cmath>
#include <climits>
#include <bitset>

CompressedBlock::CompressedBlock(std::vector<uint32_t> vec) {
    reference = *std::min_element(vec.begin(), vec.end());
    std::for_each(vec.begin(), vec.end(), [&](uint32_t &n) { n -= reference; });

    uint32_t max = *std::max_element(vec.begin(), vec.end());
    bitsToRepr = (max == 0) ? 0 : ceil(log2(max));
    compressNumbers(vec);
}

void CompressedBlock::write(std::ostream &stream) {
    uint32_t min = htobe32(reference);
    stream.write(reinterpret_cast<const char *>(&min), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&bitsToRepr), sizeof(uint8_t));

    for (uint y = 0; y < compressedNumbers.size(); y += CHAR_BIT) {
        std::string byte = compressedNumbers.substr(y, CHAR_BIT);
        unsigned long num = strtoul(byte.c_str(), NULL, 2);
        char *buffer = reinterpret_cast<char *>(&num);
        stream.write(buffer, sizeof(uint8_t));
    }
}

void CompressedBlock::compressNumbers(std::vector<uint32_t> items) {
    std::string pack;
    for (uint32_t i = 0; i < items.size(); i++) {
        std::string binary = std::bitset<sizeof(uint32_t) * CHAR_BIT>(items[i]).to_string();
        int mask = binary.size() - bitsToRepr;
        std::string importantBits = binary.substr(mask);
        pack += importantBits;
    }

    while (pack.size() % CHAR_BIT != 0)
        pack += '0';

    compressedNumbers = pack;
}