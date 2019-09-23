#include <iostream>
#include <vector>
#include <algorithm>
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
    for (int i = 0; i < nThreads; i++) {
        minions[i] = new Minion(blockSize, queueLimit, &input);
    }

//    Master master(minions, &outputStream);
//    master.start();

    std::for_each(minions.begin(), minions.end(), [&](Minion *m) { m->start(); });
    std::for_each(minions.begin(), minions.end(), [&](Minion *m) { m->join(); });

//    master.join();

    std::for_each(minions.begin(), minions.end(), [&](Minion *m) { delete m; });

    inputStream.close();
    outputStream.close();
    return 0;
}
