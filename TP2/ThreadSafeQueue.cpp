#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int elemLimit) {
    this->limit = elemLimit;
}

void ThreadSafeQueue::push(CompressedBlock block) {
    std::unique_lock<std::mutex> lock(m);
    if (queue.size() == limit)
        havePopped.wait(lock);

    queue.push(block);
    havePushed.notify_all();
}

CompressedBlock ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (queue.size() == 0)
        havePushed.wait(lock);

    CompressedBlock block = queue.front();
    queue.pop();
    havePopped.notify_all();
    return block;
}
