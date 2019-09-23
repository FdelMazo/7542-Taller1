#ifndef TP1_MINION_H
#define TP1_MINION_H

#include "Thread.h"
#include "InputMonitor.h"
#include <vector>

// Minion Class
// The minion job is to:
//    - Read from an input without stepping onto another minion's read of file
//         (The minion will read according to how many minions are available,
//              and to the id of this particular minion)
//    - Process what's read
//    - Place it on it's own public queue (which has a limited amount of items)
//
// Once the processed is on the queue, the (sole) master will take care of it

class Minion : public Thread {
    // Class variable to keep track of all the minions (threads) running
    static int minionCount;

public:
    // Constructor: initializes the attributes and increments minionCount
    Minion(int blockSize, int queueLimit, InputMonitor *input);

    // As long as the file hasn't reach the end,
    //   and there are blocks inside the valid range:
    //      - Read blockSize numbers from the file
    //      - Compress them
    //      - Place them on the queue
    void run();

private:
    // Minion's id
    int id;

    // How many numbers will the minion read from the input
    int blockSize;

    // The input from which the minion will read numbers
    InputMonitor *fileToRead;

    // Read blockSize numbers from fileToRead, starting from position start
    std::vector<uint32_t> readFile(int start);
};

#endif //TP1_MINION_H
