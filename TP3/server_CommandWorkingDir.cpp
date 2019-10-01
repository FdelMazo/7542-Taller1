#include "server_CommandWorkingDir.h"

std::string CommandWorkingDir::run(std::string dummyArg, std::string *username, std::string *password, bool *pBoolean) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    return response(RC, pot->getMsg(MSG));
}
