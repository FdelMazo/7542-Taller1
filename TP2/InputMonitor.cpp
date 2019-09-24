#include "InputMonitor.h"

InputMonitor::InputMonitor(std::istream *inputStream) {
    this->stream = inputStream;
    stream->seekg(0, std::ios::end);
    this->streamSize = stream->tellg();
    stream->seekg(0, std::ios::beg);
}

bool InputMonitor::eof(int i) {
    return i >= streamSize;
}

void InputMonitor::read(char *buffer, size_t n, int pos) {
    std::unique_lock<std::mutex> lock(m);
    stream->seekg(pos);
    stream->read(buffer, n);
}
