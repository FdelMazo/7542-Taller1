#ifndef TP1_INPUTMONITOR_H
#define TP1_INPUTMONITOR_H

#include <mutex>
#include <fstream>

// InputMonitor Class
// This monitor takes care of having a civilized read from the input
// Any thread who wants to read from the file must first aquire the lock

class InputMonitor {
private:
    // The file lock to aquire
    std::mutex lock;

    // The resource everyone is racing to get to
    std::ifstream *file;

    // The file size, to know it's bounds
    int fileSize;

public:
    // Constructor
    InputMonitor(std::ifstream *inputStream);

    // Returns if a position is valid or not (past the EOF)
    bool eof(int i);

    // Read n bytes from file, starting in pos, and stores them in buffer
    void read(char *buffer, size_t n, int pos);
};

#endif //TP1_INPUTMONITOR_H
