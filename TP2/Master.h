#ifndef TP1_MASTER_H
#define TP1_MASTER_H

#include <vector>
#include "Thread.h"
#include "Minion.h"
#include "ThreadSafeQueue.h"

class Master : public Thread {
public:
    Master(std::vector<Minion *> vector, std::ofstream *pOfstream);

    ~Master();
    void run();
private:
    std::vector<ThreadSafeQueue *> queues;
    std::ofstream *file;
};


#endif //TP1_MASTER_H







