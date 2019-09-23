#ifndef TP1_COMPRESSEDBLOCK_H
#define TP1_COMPRESSEDBLOCK_H

#include <vector>
#include <cstdint>
#include <istream>

// CompressedBlock class
// This class serves as a compressor for a vector of numbers
// Compressor technique: frame of reference
// It receives 4-byte numbers which are all similar in value, then:
//    - It gets the reference value (the similar to all of them)
//    - It substracts the reference to all of them, leaving very small numbers
//    - It compresses the whole lot of small numbers, by bitpacking

class CompressedBlock {
public:
    // Given a vector of 4-byte numbers, it compresses them all
    // Everything needed for the block is stored in the members of the class
    CompressedBlock(std::vector<uint32_t> vec);

    // Writes the compressed block to the given stream
    void write(std::ostream &stream);

    bool isInvalid();

private:
    // Reference value
    uint32_t reference;

    // How many bits are needed to represent each number
    uint8_t bitsToRepr;

    // All the numbers, converted to a string of bits
    std::string compressedNumbers;

    // Method to pass from the vector of (small) numbers to a string of bits
    void compressNumbers(std::vector<uint32_t> items);

    bool invalid;
};


#endif //TP1_COMPRESSEDBLOCK_H
