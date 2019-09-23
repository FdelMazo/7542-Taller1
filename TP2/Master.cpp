#include "Master.h"
#include "CompressedBlock.h"

Master::Master(std::vector<Minion *> minions, std::ostream *output) {
    this->file = output;
    this->queues = std::vector<ThreadSafeQueue *>(minions.size());
    for (uint i = 0; i < minions.size(); i++) {
        queues[i] = minions[i]->queue;
    }
}

void Master::run() {
    bool keepWriting = true;
    while (keepWriting) {
        for (uint i = 0; i < queues.size(); i++) {
            CompressedBlock block = queues[i]->pop();
            keepWriting &= block.valid();
            block.write(*file);
        }
    }
}

Master::~Master() {
    this->join();
}
