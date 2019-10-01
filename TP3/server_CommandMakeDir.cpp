#include "server_CommandMakeDir.h"

std::string CommandMakeDir::run(std::string dirName) {
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    if (pot->mkDir(dirName))
        return response(257, pot->getAnswer("mkdSuccess"), dirName);
    return response(550, pot->getAnswer("mkdFailed"));
}
