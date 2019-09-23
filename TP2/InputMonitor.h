//
// Created by delmazo on 9/22/19.
//

#ifndef TP1_INPUTMONITOR_H
#define TP1_INPUTMONITOR_H


#include <mutex>
#include <bits/ios_base.h>
#include <fstream>

class InputMonitor {
    std::mutex lock;
    std::ifstream *file;
public:

    InputMonitor(std::ifstream *inputStream);

    bool eof(int i);

    void read(char *string, size_t i, int j);

    int fileSize;
};


#endif //TP1_INPUTMONITOR_H
