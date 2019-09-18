#ifndef TP1_BLOCK_H
#define TP1_BLOCK_H


#include <vector>
#include <cstdint>
#include <istream>

class Block {

public:
    Block(int i);

    void readFile(std::basic_istream<char> &istream);

    void process();

    void write(std::ostream &ostream);

private:
    std::vector<uint32_t> items;
    uint32_t reference;
    uint8_t bitsToRepr;
    std::string bitsToWrite;

    void itemsToString();
};


#endif //TP1_BLOCK_H
