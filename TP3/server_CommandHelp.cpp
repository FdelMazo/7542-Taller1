#include "server_CommandHelp.h"

std::string CommandHelp::run(std::string dummyArg) {
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    return response(214, pot->getAnswer("commands"));
}
