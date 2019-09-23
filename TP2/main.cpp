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
    std::vector<Minion *> minions(atoi(argv[2]));
    for (uint i = 0; i < minions.size(); i++) {
        minions[i] = new Minion(atoi(argv[1]), atoi(argv[3]), &input);
    }

    Master *master = new Master(minions, outputStream);
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
