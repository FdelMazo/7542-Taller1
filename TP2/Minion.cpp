#include "Minion.h"
#include "CompressedBlock.h"

int Minion::minionCount = 0;

Minion::Minion(int blockSize, int queueLimit, InputMonitor *input) {
    this->blockSize = blockSize;
    this->fileToRead = input;
    this->id = minionCount;
    minionCount++;
}

void Minion::run() {
    int start = id * blockSize * sizeof(uint32_t);
    int step = minionCount * blockSize * sizeof(uint32_t);
    for (int i = start; !fileToRead->eof(i); i += step) {
        std::vector<uint32_t> blockNumbers = readFile(i);
        CompressedBlock block(blockNumbers);
    }
}

std::vector<uint32_t> Minion::readFile(int positionToStart) {
    std::vector<uint32_t> blockNumbers(blockSize);
    int positionToRead = positionToStart;
    for (int i = 0; i < blockSize; i++) {
        if (!fileToRead->eof(i)) {
            uint32_t num;
            char *buffer = reinterpret_cast<char *>(&num);
            fileToRead->read(buffer, sizeof(uint32_t), positionToRead);
            blockNumbers[i] = be32toh(num);
        } else {
            // Padding: fill the block with the last number read
            blockNumbers[i] = blockNumbers[i - 1];
        }
        positionToRead += sizeof(uint32_t);
    }
    return blockNumbers;
}

