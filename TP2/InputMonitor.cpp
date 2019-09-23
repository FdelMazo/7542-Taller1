//
// Created by delmazo on 9/22/19.
//

#include <iostream>
#include "InputMonitor.h"

InputMonitor::InputMonitor(std::ifstream *inputStream) {
    this->file = inputStream;
    file->seekg(0, std::ios::end);
    this->fileSize = file->tellg();
    file->seekg(0, std::ios::beg);
}

bool InputMonitor::eof(int i) {
    return i >= fileSize;
}

void InputMonitor::read(char *string, size_t i, int position) {
    std::unique_lock<std::mutex> l(lock);
    file->seekg(position);
    file->read(string, i);
}
