#ifndef TP1_MASTER_H
#define TP1_MASTER_H

#include <vector>
#include "Thread.h"
#include "Minion.h"
#include "ThreadSafeQueue.h"

// Master Class
// The master works concurrently with the minions
// Taking elements from the minions queues, it then writes everything to the out

class Master : public Thread {
public:
    // Constructor: It initializes the queues, by taking them from the minions
    // (it also assigns the output stream, for then to write)
    Master(const std::vector<Minion *> vector, std::ostream *output);

    // While the minions keep pushing everything to their queues,
    //    the master grabs those elements, and starts writing them to the out
    // It does this on a round robin style: Take one element from each, in order
    // From this point of view, a queue is never empty,
    //     because they internally are refilled whenever they have a pop
    // It only stops running when each minion pushed the invalid block
    // (an invalid block is the minions signal that it has pushed everything)
    void run();

private:
    // Every minions queue, which the minion fills
    std::vector<ThreadSafeQueue *> queues;

    // Output stream, where the block will be written
    std::ostream *streamTowrite;
};


#endif //TP1_MASTER_H







