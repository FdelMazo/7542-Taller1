#include "server_CommandSystemInfo.h"

std::string CommandSystemInfo::run(std::string dummyArg, std::string *username, std::string *password, bool *pBoolean) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    return response(215, pot->getMsg("systemInfo"));
//    return response(RC, pot->getMsg(MSG));
}
