#include "ThreadSafeQueue.h"

ThreadSafeQueue::ThreadSafeQueue(int elemLimit) {
    this->limit = elemLimit;
}

void ThreadSafeQueue::push(CompressedBlock block) {
    std::unique_lock<std::mutex> lock(m);
    queue.push(block);
    cond_var.notify_all();
}

CompressedBlock ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> lock(m);
    while (queue.size() == 0)
        cond_var.wait(lock);

    CompressedBlock block = queue.front();
    queue.pop();
    return block;
}
