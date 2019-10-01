#include "server_CommandWorkingDir.h"

std::string CommandWorkingDir::run(std::string dummyArg) {
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    return response(257, pot->getAnswer("currentDirectoryMsg"));
}
