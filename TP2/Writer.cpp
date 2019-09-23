#include "Writer.h"
#include "CompressedBlock.h"
#include <vector>

void Writer::run() {
    bool keepPoping = true;
    while (keepPoping) {
        for (uint i = 0; i < queues.size(); i++) {
            CompressedBlock block = queues[i]->pop();
            if (block.isInvalid()) {
                keepPoping = false;
                continue;
            }
            block.write(*file);
        }
    }
}

Writer::Writer(std::vector<Minion *> minions, std::ofstream *output) {
    this->file = output;
    this->queues = std::vector<ThreadSafeQueue *>(minions.size());
    for (uint i = 0; i < minions.size(); i++) {
        queues[i] = minions[i]->queue;
    }
}
