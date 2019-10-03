#include <vector>
#include "Minion.h"
#include "CompressedBlock.h"

Minion::Minion(int blockSize, int queueLimit, InputMonitor *input,
        int myId, int totalCount) : queue(queueLimit){
    this->blockSize = blockSize;
    this->id = myId;
    this->streamToRead = input;
    this->minionCount = totalCount;
}

void Minion::run() {
    int start = id * blockSize * sizeof(uint32_t);
    int step = minionCount * blockSize * sizeof(uint32_t);
    for (uint i = start; !streamToRead->validPosition(i); i += step) {
        std::vector<uint32_t> blockNumbers = readFile(i);
        CompressedBlock block(blockNumbers);
        queue.push(block);
    }

    // When the queue has all the minion blocks,
    //     push an invalid block for the master to handle
    std::vector<uint32_t> empty(0);
    CompressedBlock nullBlock(empty);
    queue.push(nullBlock);
}

std::vector<uint32_t> Minion::readFile(int positionToStart) {
    std::vector<uint32_t> blockNumbers(blockSize);
    int positionToRead = positionToStart;
    for (int i = 0; i < blockSize; i++) {
        uint32_t num;
        char *buffer = reinterpret_cast<char *>(&num);
        bool r = streamToRead->read(buffer, sizeof(uint32_t), positionToRead);
        if (r)
            blockNumbers[i] = be32toh(num);
        else
            blockNumbers[i] = blockNumbers[i-1];
        positionToRead += sizeof(uint32_t);
    }
    return blockNumbers;
}
