#include "server_CommandWorkingDir.h"

std::string CommandWorkingDir::run(std::string &dummyArg, bool *alive) {
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    return response(257, pot->getAnswer("currentDirectoryMsg"));
}
