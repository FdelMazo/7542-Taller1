#ifndef TP1_THREADSAFEQUEUE_H
#define TP1_THREADSAFEQUEUE_H

#include <queue>
#include <condition_variable>
#include "CompressedBlock.h"

class ThreadSafeQueue {
public:
    explicit ThreadSafeQueue(int elemLimit);
    int limit;
    void push(CompressedBlock block);
    CompressedBlock pop();

private:
    std::condition_variable cond_var;
    std::mutex m;
    std::queue<CompressedBlock> queue;
};


#endif //TP1_THREADSAFEQUEUE_H
