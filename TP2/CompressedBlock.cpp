#include <algorithm>
#include <cmath>
#include <climits>
#include <bitset>
#include "CompressedBlock.h"

CompressedBlock::CompressedBlock(std::vector<uint32_t> vector) {
    std::vector<uint32_t> numbers = vector;
    reference = *std::min_element(numbers.begin(), numbers.end());
    for (uint32_t i = 0; i < numbers.size(); i++)
        numbers[i] -= reference;
    uint32_t max = *std::max_element(numbers.begin(), numbers.end());
    bitsToRepr = (max == 0) ? 0 : ceil(log2(max));
    compressNumbers(numbers);
}

void CompressedBlock::write(std::ostream &stream) {
    uint32_t min = htobe32(reference);
    stream.write(reinterpret_cast<const char *>(&min), sizeof(uint32_t));
    stream.write(reinterpret_cast<const char *>(&bitsToRepr), sizeof(uint8_t));

    for (uint y = 0; y < compressedNumbers.size(); y += CHAR_BIT) {
        std::string byte = compressedNumbers.substr(y, CHAR_BIT);
        unsigned long ul = strtoul(byte.c_str(), NULL, 2);
        uint8_t x = (uint8_t) ul;
        stream.write(reinterpret_cast<const char *>(&x), sizeof(uint8_t));
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