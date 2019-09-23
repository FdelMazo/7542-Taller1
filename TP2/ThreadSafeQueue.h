#ifndef TP1_THREADSAFEQUEUE_H
#define TP1_THREADSAFEQUEUE_H

#include <queue>
#include <condition_variable>
#include "CompressedBlock.h"

class ThreadSafeQueue {
public:
    explicit ThreadSafeQueue(int elemLimit);

    uint limit;
    void push(CompressedBlock block);
    CompressedBlock pop();

private:
    std::mutex m;
    std::condition_variable havePushed;
    std::condition_variable havePopped;
    std::queue<CompressedBlock> queue;
};


#endif //TP1_THREADSAFEQUEUE_H
