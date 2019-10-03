#include "StreamHandler.h"
#include <fstream>
#include <cstring>
#include <string>

std::istream *StreamHandler::getInput(char *filename) {
    bool inputIsFile = (std::string(filename) != std::string(STREAM));
    inputFile = new std::ifstream;
    if (inputIsFile) {
        inputFile->open(filename, std::ios::out | std::ios::binary);
        if (!inputFile) return nullptr;
    }
    std::istream &inputStream = inputIsFile ? *inputFile : std::cin;
    return &inputStream;
}

std::ostream *StreamHandler::getOutput(char *filename) {
    bool outputIsFile = strncmp(filename, STREAM, strlen(filename));
    outputFile = new std::ofstream;
    if (outputIsFile) {
        outputFile->open(filename, std::ios::out | std::ios::binary);
        if (!outputFile) return nullptr;
    }
    std::ostream &outputStream = outputIsFile ? *outputFile : std::cout;
    return &outputStream;
}

StreamHandler::~StreamHandler() {
    delete inputFile;
    delete outputFile;
}
