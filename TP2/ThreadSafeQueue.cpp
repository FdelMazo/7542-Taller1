#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int elemLimit) {
    this->limit = elemLimit;
}

void ThreadSafeQueue::push(CompressedBlock block) {
    std::unique_lock<std::mutex> lock(m);
    while (queue.size() == limit)
        poped.wait(lock);

    queue.push(block);
    pushed.notify_all();
}

CompressedBlock ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (queue.size() == 0)
        pushed.wait(lock);

    CompressedBlock block = queue.front();
    queue.pop();
    poped.notify_all();
    return block;
}
