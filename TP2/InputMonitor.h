#ifndef TP1_INPUTMONITOR_H
#define TP1_INPUTMONITOR_H

#include <mutex>
#include <fstream>

// InputMonitor Class
// This monitor takes care of having a civilized read from the input
// Any thread who wants to read from the file must first acquire the m

class InputMonitor {
public:
    // Creates a monitor for the inputStream
    explicit InputMonitor(std::istream *inputStream);

// Returns if a position is valid or not (past the EOF)
    bool eof(int i);

    // Read n bytes from file, starting in pos, and stores them in buffer
    void read(char *buffer, size_t n, int pos);

private:
    // The file m to acquire
    std::mutex m;

    // The resource everyone is racing to get to
    std::istream *file;

    // The file valid, to know it's bounds
    int fileSize;
};

#endif //TP1_INPUTMONITOR_H
