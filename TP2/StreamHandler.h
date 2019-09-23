#ifndef TP1_STREAMHANDLER_H
#define TP1_STREAMHANDLER_H

#include <iostream>
#include <string>

class StreamHandler {
public:
    static constexpr const char *STREAM = "-";

    std::istream *getInput(char *filename);

    std::ostream *getOutput(char *filename);

    ~StreamHandler();

private:
    std::ifstream *inputFile;
    std::ofstream *outputFile;
};


#endif //TP1_STREAMHANDLER_H
