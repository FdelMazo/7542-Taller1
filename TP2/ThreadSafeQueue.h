#ifndef TP1_THREADSAFEQUEUE_H
#define TP1_THREADSAFEQUEUE_H

#include <queue>
#include <condition_variable>
#include "CompressedBlock.h"

// Thread Safe Queue Class
// Wrapper over the STL FIFO queue, to make it appropriate for multithreading

class ThreadSafeQueue {
public:
    // Constructor: Creates a queue which can have up to elemLimit elements
    explicit ThreadSafeQueue(int elemLimit);

    // Push to the queue.
    // If it is 'full' (up to the limit),
    //     it waits for the conditional variable to notify that it can push
    // It then notifies that it has just pushed, as for the pop to work
    void push(CompressedBlock block);

    // Pop the last element
    // If the queue is empty,
    //    it waits for the cond var to notify that something was pushed
    // It then notifies that something was popped,
    //   so that if the limit was reached, now a new push can be made
    CompressedBlock pop();

private:
    // Internal STL queue, the real MVP
    std::queue<CompressedBlock> queue;

    // Max number of elements to contain
    uint limit;

    // Mutex, for a lock to keep threads from moving elements at the same time
    std::mutex m;

    // Conditional variable to notify that an element was just pushed
    std::condition_variable poped;
    // Conditional variable to notify that an element was just popped
    std::condition_variable pushed;
};

#endif //TP1_THREADSAFEQUEUE_H
