#include <algorithm>
#include <cmath>
#include <climits>
#include <bitset>
#include "Block.h"

Block::Block(int n) {
    items = std::vector<uint32_t>(n);
}

void Block::readFile(std::basic_istream<char> &input) {
    for (uint32_t i = 0; i < items.size(); i++) {
        if (input.peek() != EOF) {
            uint32_t num;
            input.read(reinterpret_cast<char *>(&num), sizeof(uint32_t));
            items[i] = be32toh(num);
        } else {
            items[i] = items[i - 1];
        }
    }
}

void Block::itemsToString() {
    std::string pack;
    for (uint32_t i = 0; i < items.size(); i++) {
        std::string binary = std::bitset<sizeof(uint32_t) * CHAR_BIT>
                (items[i]).to_string();
        int mask = binary.size() - bitsToRepr;
        std::string importantBits = binary.substr(mask);
        pack += importantBits;
    }

    while (pack.size() % CHAR_BIT != 0)
        pack += '0';

    bitsToWrite = pack;
}

void Block::process() {
    reference = *std::min_element(items.begin(), items.end());
    for (uint32_t i = 0; i < items.size(); i++)
        items[i] -= reference;
    uint32_t max = *std::max_element(items.begin(), items.end());
    bitsToRepr = (max == 0) ? 0 : ceil(log2(max));
    itemsToString();
}

void Block::write(std::ostream &output) {
    uint32_t min = htobe32(reference);
    output.write(reinterpret_cast<const char *>(&min), sizeof(uint32_t));
    output.write(reinterpret_cast<const char *>(&bitsToRepr), sizeof(uint8_t));

    for (uint y = 0; y < bitsToWrite.size(); y += CHAR_BIT) {
        std::string byte = bitsToWrite.substr(y, CHAR_BIT);
        unsigned long ul = strtoul(byte.c_str(), NULL, 2);
        uint8_t x = (uint8_t) ul;
        output.write(reinterpret_cast<const char *>(&x), sizeof(uint8_t));
    }
}


