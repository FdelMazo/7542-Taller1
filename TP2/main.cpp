#include <bitset>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <cmath>

int main(int argc, char *argv[]) {
    std::ifstream input;
    input.open(argv[4], std::ios::in | std::ios::binary);
    std::string line;
    int blockn = atoi(argv[1]);

    std::vector <uint32_t> block(blockn);
    for (uint32_t i = 0; i < block.size(); i++) {
        uint32_t myint;
        input.read(reinterpret_cast<char *>(&myint), sizeof(uint32_t));
        block[i] = be32toh(myint);
    }

    uint32_t min = *std::min_element(block.begin(), block.end());

    for (uint32_t i = 0; i < block.size(); i++) {
        block[i] -= min;
    }

    uint32_t max = *std::max_element(block.begin(), block.end());
    int bits = ceil(log2(max));

    min = htobe32(min);

    std::ofstream output;
    output.open(argv[5], std::ios::out | std::ios::binary);
    output.write(reinterpret_cast<const char *>(&min), sizeof(uint32_t));
    output.write(reinterpret_cast<const char *>(&bits), sizeof(uint8_t));

    std::string pack;
    for (uint32_t i = 0; i < block.size(); i++) {
        std::string binary = std::bitset<sizeof(uint32_t)>(block[i]).to_string();
        std::string importantBits = binary.substr(bits);
        pack += importantBits;
    }

    unsigned long ul;
    ul = strtoul(pack.c_str(), NULL, 2);
    uint8_t x = (uint8_t) ul;

    output.write(reinterpret_cast<const char *>(&x), sizeof(uint8_t));

    input.close();
    output.close();
    return 0;
}
