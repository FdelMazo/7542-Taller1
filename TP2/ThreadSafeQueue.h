#ifndef TP1_THREADSAFEQUEUE_H
#define TP1_THREADSAFEQUEUE_H

#include <queue>
#include <condition_variable>
#include "CompressedBlock.h"

class ThreadSafeQueue {
private:
    std::condition_variable cond_var;
public:
    explicit ThreadSafeQueue(int elemLimit);

    ThreadSafeQueue();

    int limit;
    std::queue<CompressedBlock> queue;

    void push(CompressedBlock block);

    CompressedBlock pop();

    std::mutex lock;
};


#endif //TP1_THREADSAFEQUEUE_H
