#include <iostream>
#include <string>
#include <cmath>
#include "CompressedBlock.h"
#include "Minion.h"
#include "Master.h"

int main(int argc, char *argv[]) {
    if (argc != 6) return 1;
    int blockSize = atoi(argv[1]);
    int nThreads = atoi(argv[2]);
    int queueLimit = atoi(argv[3]);
    std::ifstream inputStream(argv[4], std::ios::out | std::ios::binary);
    std::ofstream outputStream(argv[5], std::ios::out | std::ios::binary);

    InputMonitor input(&inputStream);

    std::vector<Minion *> minions(nThreads);

    for (int i = 0; i < nThreads; i++) {
        minions[i] = new Minion(blockSize, queueLimit, &input);
    }


//    Master master(minions, &outputStream);
//    master.start();

    for (int i = 0; i < nThreads; i++) {
        minions[i]->start();
    }

    for (int i = 0; i < nThreads; i++) {
        minions[i]->join();
    }

//     join de master
//     deletes

    inputStream.close();
    outputStream.close();
    return 0;
}
