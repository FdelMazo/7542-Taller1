#include <iostream>
#include <vector>
#include "Master.h"
#include "Minion.h"

int main(int argc, char *argv[]) {
    if (argc != 6) return 1;
    int blockSize = atoi(argv[1]);
    int nThreads = atoi(argv[2]);
    int queueLimit = atoi(argv[3]);

    std::ifstream inputStream(argv[4], std::ios::out | std::ios::binary);
    if (!inputStream) return 1;
    std::ofstream outputStream(argv[5], std::ios::out | std::ios::binary);
    if (!outputStream) return 1;

    InputMonitor input(&inputStream);

    std::vector<Minion *> minions(nThreads);
    for (uint i = 0; i < minions.size(); i++) {
        minions[i] = new Minion(blockSize, queueLimit, &input);
    }

    Master *master = new Master(minions, &outputStream);
    master->start();

    for (uint i = 0; i < minions.size(); i++) {
        minions[i]->start();
    }

    delete master;
    for (uint i = 0; i < minions.size(); i++) {
        delete minions[i];
    }

    return 0;
}
