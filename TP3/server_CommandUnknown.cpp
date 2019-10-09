#include "server_CommandUnknown.h"

std::string CommandUnknown::run(std::string &dummyArg, bool *alive) {
    return response(530, pot->getAnswer("unknownCommand"));
}
