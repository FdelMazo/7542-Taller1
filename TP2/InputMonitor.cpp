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

void InputMonitor::read(char *buffer, size_t n, int pos) {
    std::unique_lock<std::mutex> l(lock);
    file->seekg(pos);
    file->read(buffer, n);
}
