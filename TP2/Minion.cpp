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
    for (int i = 0, positionToRead = positionToStart; i < blockSize; i++, positionToRead += sizeof(uint32_t)) {
        if (!fileToRead->eof(i)) {
            uint32_t num;
            fileToRead->read(reinterpret_cast<char *>(&num), sizeof(uint32_t), positionToRead);
            blockNumbers[i] = be32toh(num);
        } else {
            blockNumbers[i] = blockNumbers[i - 1];
        }
    }
    return blockNumbers;
}

