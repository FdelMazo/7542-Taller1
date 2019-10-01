#include "server_CommandHelp.h"

std::string CommandHelp::run(std::string dummyArg, std::string *username, std::string *password) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    return response(RC, pot->getMsg(MSG));
}
