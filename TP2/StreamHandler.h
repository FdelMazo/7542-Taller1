#ifndef TP1_STREAMHANDLER_H
#define TP1_STREAMHANDLER_H

#include <iostream>
#include <string>

class StreamHandler {
public:
    // If the filename is STREAM, then instead of opening a file,
    //     cin or cout are used
    static constexpr const char *STREAM = "-";

    // Return a stream to either cin/cout or the input/file file specified
    std::istream *getInput(char *filename);
    std::ostream *getOutput(char *filename);

    // Destructor
    ~StreamHandler();

private:
    // References to the file streams are kept
    // They live on the heap, and then are free'd by the destructor
    std::ifstream *inputFile;
    std::ofstream *outputFile;
};


#endif //TP1_STREAMHANDLER_H
