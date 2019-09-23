#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int elemLimit) {
    this->limit = elemLimit;
}

void ThreadSafeQueue::push(CompressedBlock block) {
    std::unique_lock<std::mutex> l(lock);
    queue.push(block);
    cond_var.notify_all();
}

CompressedBlock ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> l(lock);
    while (queue.size() == 0)
        cond_var.wait(l);

    CompressedBlock b = queue.front();
    queue.pop();
    return b;
}

ThreadSafeQueue::ThreadSafeQueue() {}
