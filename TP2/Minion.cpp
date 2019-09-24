#include <vector>
#include "Minion.h"
#include "CompressedBlock.h"

int Minion::minionCount = 0;

Minion::Minion(int blockSize, int queueLimit, InputMonitor *input) {
    this->blockSize = blockSize;
    this->id = minionCount;
    this->streamToRead = input;
    this->queue = new ThreadSafeQueue(queueLimit);
    minionCount++;
}

Minion::~Minion() {
    this->join();
    delete this->queue;
}

void Minion::run() {
    int start = id * blockSize * sizeof(uint32_t);
    int step = minionCount * blockSize * sizeof(uint32_t);
    for (uint i = start; !streamToRead->eof(i); i += step) {
        std::vector<uint32_t> blockNumbers = readFile(i);
        CompressedBlock block(blockNumbers);
        queue->push(block);
    }

    // When the queue has all the minion blocks,
    //     push an invalid block for the master to handle
    std::vector<uint32_t> empty(0);
    CompressedBlock nullBlock(empty);
    queue->push(nullBlock);
}

std::vector<uint32_t> Minion::readFile(int positionToStart) {
    std::vector<uint32_t> blockNumbers(blockSize);
    int positionToRead = positionToStart;
    for (int i = 0; i < blockSize; i++) {
        if (!streamToRead->eof(positionToRead)) {
            uint32_t num;
            char *buffer = reinterpret_cast<char *>(&num);
            streamToRead->read(buffer, sizeof(uint32_t), positionToRead);
            blockNumbers[i] = be32toh(num);
        } else {
            // Padding: fill the block with the last number read
            blockNumbers[i] = blockNumbers[i - 1];
        }
        positionToRead += sizeof(uint32_t);
    }
    return blockNumbers;
}
