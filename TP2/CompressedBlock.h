#ifndef TP1_COMPRESSEDBLOCK_H
#define TP1_COMPRESSEDBLOCK_H


#include <vector>
#include <cstdint>
#include <istream>

class CompressedBlock {

public:
    CompressedBlock(std::vector<uint32_t> vector);
    void write(std::ostream &ostream);
private:
    uint32_t reference;
    uint8_t bitsToRepr;
    std::string compressedNumbers;

    void compressNumbers(std::vector<uint32_t> items);
};


#endif //TP1_COMPRESSEDBLOCK_H
