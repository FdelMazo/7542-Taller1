#include "server_CommandUnknown.h"

std::string CommandUnknown::run(std::string dummyArg) {
    return response(530, pot->getAnswer("unknownCommand"));
}
