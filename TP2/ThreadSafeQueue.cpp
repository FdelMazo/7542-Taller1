#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int elemLimit) {
    this->limit = elemLimit;
}

void ThreadSafeQueue::push(CompressedBlock block) {
    std::unique_lock<std::mutex> lock(m);
    while (queue.size() == limit)
        condition.wait(lock);

    queue.push(block);
    condition.notify_all();
}

CompressedBlock ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (queue.size() == 0)
        condition.wait(lock);

    CompressedBlock block = queue.front();
    queue.pop();
    condition.notify_all();
    return block;
}
