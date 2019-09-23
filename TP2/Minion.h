#ifndef TP1_MINION_H
#define TP1_MINION_H

#include <mutex>
#include <fstream>
#include "Thread.h"
#include "RoundRobinQueue.h"
#include "InputMonitor.h"

class Minion : public Thread {
private:
    static int minionCount;
    int blockSize;
    InputMonitor *fileToRead;
    int id;

public:
    void run();

    Minion(int blockSize, int queueLimit, InputMonitor *input);

    void compressBlock(int start);

    std::vector<uint32_t> readFile(int start);
};

#endif //TP1_MINION_H
