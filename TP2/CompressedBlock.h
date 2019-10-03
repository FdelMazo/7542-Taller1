#ifndef TP1_COMPRESSEDBLOCK_H
#define TP1_COMPRESSEDBLOCK_H

#include <vector>
#include <cstdint>
#include <istream>
#include <string>

// CompressedBlock Class
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
    explicit CompressedBlock(std::vector<uint32_t> vec);

    // A block isn't valid when it has no reference
    // AKA, when it was created with an empty vector, for example
    // (A frame of reference block without reference doesn't work...)
    bool valid();

    // Writes the compressed block to the given stream
    void write(std::ostream &stream);

private:
    // Reference value
    uint32_t reference = 0;

    // How many bits are needed to represent each number
    uint8_t bitsToRepr;

    // All the numbers, converted to a string of bits
    std::string compressedNumbers;

    // Method to pass from the vector of (small) numbers to a string of bits
    std::string compressNumbers(const std::vector<uint32_t> vec);
};


#endif //TP1_COMPRESSEDBLOCK_H
