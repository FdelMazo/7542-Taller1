#include <bitset>
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

int main(int argc, char *argv[]) {
    std::ifstream input;
    input.open(argv[4], std::ios::in | std::ios::binary);
    std::ofstream output;
    output.open(argv[5], std::ios::out | std::ios::binary);

    uint32_t blockSize = atoi(argv[1]);

    while ( input.peek() != EOF ) {
        std::vector<uint32_t> block(blockSize);
//        std::cerr << "Block to compress: ";
        for (uint32_t i = 0; i < block.size(); i++) {
            if (input.peek() != EOF) {
                uint32_t num;
                input.read(reinterpret_cast<char *>(&num), sizeof(uint32_t));
                block[i] = be32toh(num);
            } else {
                block[i] = block[i - 1];
            }
//            std::cerr << block[i] << " - ";
        }
//        std::cerr << '\n';

        uint32_t min = *std::min_element(block.begin(), block.end());
//        std::cerr << "Ref in block: " << min << "; ";

//        std::cerr << "Now turned to: ";
        for (uint32_t i = 0; i < block.size(); i++) {
            block[i] -= min;
//            std::cerr << block[i] << " - ";
        }
//        std::cerr << '\n';

        uint32_t max = *std::max_element(block.begin(), block.end());
        int bitsToRepr = (max == 0) ? 0 : ceil(log2(max));

//        std::cerr << "Max in block: " << max << "; ";
//        std::cerr << "Bits neccesary to represent: " << bitsToRepr << "; ";

        min = htobe32(min);
        output.write(reinterpret_cast<const char *>(&min), sizeof(uint32_t));
        output.write(reinterpret_cast<const char *>(&bitsToRepr),
                sizeof(uint8_t));

        std::string pack;
        for (uint32_t i = 0; i < block.size(); i++) {
            std::string binary = std::bitset<sizeof(uint32_t) * CHAR_BIT>
                    (block[i]).to_string();
            int mask = binary.size() - bitsToRepr;
            std::string importantBits = binary.substr(mask);
            pack += importantBits;
        }
        while (pack.size() % CHAR_BIT != 0) {
            pack += '0';
        }
        for (uint y = 0; y < pack.size(); y+=CHAR_BIT) {
            std::string byte = pack.substr(y, CHAR_BIT);
            unsigned long ul = strtoul(byte.c_str(), NULL, 2);
            uint8_t x = (uint8_t) ul;
            output.write(reinterpret_cast<const char *>(&x), sizeof(uint8_t));
        }
//        std::cerr << "\n\n";
    }

    input.close();
    output.close();
    return 0;
}
