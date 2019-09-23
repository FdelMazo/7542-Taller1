#ifndef TP1_WRITER_H
#define TP1_WRITER_H

#include <vector>
#include "Thread.h"
#include "Minion.h"
#include "ThreadSafeQueue.h"

class Writer : public Thread {
public:
    Writer(std::vector<Minion *> vector, std::ofstream *pOfstream);

    void run();

    std::vector<ThreadSafeQueue *> queues;

private:
    std::ofstream *file;
};


#endif //TP1_WRITER_H







