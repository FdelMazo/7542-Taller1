#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstring>
#include "Block.h"

int main(int argc, char *argv[]) {
    if (argc != 6) return 1;

    std::ifstream inputStream;
    bool inputIsFile = strncmp(argv[4], "-", strlen(argv[4]));
    if (inputIsFile)
        inputStream.open(argv[4], std::ios::out | std::ios::binary);

    std::istream &input = inputIsFile ? inputStream : std::cin;
    if (!input) return 1;

    std::ofstream outputStream;
    bool outputIsFile = strncmp(argv[5], "-", strlen(argv[5]));
    if (outputIsFile)
        outputStream.open(argv[5], std::ios::out | std::ios::binary);

    std::ostream &output = outputIsFile ? outputStream : std::cout;
    if (!output) return 1;

    int blockSize = atoi(argv[1]);

    while ( input.peek() != EOF ) {
        Block block(blockSize);
        block.readFile(input);
        block.process();
        block.write(output);
    }

    if (inputIsFile)
        inputStream.close();
    if (outputIsFile)
        outputStream.close();
    return 0;
}
