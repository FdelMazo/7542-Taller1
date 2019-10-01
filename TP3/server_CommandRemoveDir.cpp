#include "server_CommandRemoveDir.h"

std::string CommandRemoveDir::run(std::string dirName, bool *alive) {
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    if (pot->rmDir(dirName))
        return response(250, pot->getAnswer("rmdSuccess"), dirName);
    return response(550, pot->getAnswer("rmdFailed"));
}
