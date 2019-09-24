#include "Master.h"
#include "CompressedBlock.h"
#include <vector>

Master::Master(std::vector<Minion *> minions, std::ostream *output) {
    this->fileToWrite = output;
    this->queues = std::vector<ThreadSafeQueue *>(minions.size());
    for (uint i = 0; i < minions.size(); i++) {
        queues[i] = minions[i]->queue;
    }
}

Master::~Master() {
    this->join();
}

void Master::run() {
    bool keepWriting = true;
    while (keepWriting) {
        for (uint i = 0; i < queues.size(); i++) {
            CompressedBlock block = queues[i]->pop();
            keepWriting &= block.valid();
            block.write(*fileToWrite);
        }
    }
}

