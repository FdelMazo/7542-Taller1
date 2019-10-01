#include "server_CommandSystemInfo.h"

std::string CommandSystemInfo::run(std::string dummyArg) {
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    return response(215, pot->getAnswer("systemInfo"));
}
