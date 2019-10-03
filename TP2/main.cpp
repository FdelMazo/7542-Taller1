#include <vector>
#include "Master.h"
#include "Minion.h"
#include "StreamHandler.h"


int main(int argc, char *argv[]) {
    if (argc != 6) return 1;
    StreamHandler streams;
    std::istream *inputStream = streams.getInput(argv[4]);
    if (!inputStream) return 1;
    std::ostream *outputStream = streams.getOutput(argv[5]);
    if (!outputStream) return 1;

    InputMonitor input(inputStream);

    int blockSize = atoi(argv[1]);
    int minionCount = atoi(argv[2]);
    int queueLimit = atoi(argv[2]);
    std::vector<Minion *> minions(minionCount);
    for (uint i = 0; i < minions.size(); i++) {
        minions[i] = new Minion(blockSize, queueLimit,
                &input, i, minionCount);
    }

    Master master(minions, outputStream);
    master.start();

    for (uint i = 0; i < minions.size(); i++) {
        minions[i]->start();
    }

    master.join();
    for (uint i = 0; i < minions.size(); i++) {
        minions[i]->join();
        delete minions[i];
    }

    return 0;
}
