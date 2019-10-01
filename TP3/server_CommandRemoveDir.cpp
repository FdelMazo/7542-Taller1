#include "server_CommandRemoveDir.h"

std::string CommandRemoveDir::run(std::string dirName, std::string *username, std::string *password, bool *pBoolean) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    if (pot->rmDir(dirName))
        return response(250, pot->getMsg("rmdSuccess"), dirName);
//        return response(SUCCESS_RC, pot->getMsg(SUCCESS_MSG));
//    return response(FAILED_RC, pot->getMsg(FAILED_MSG));
    return response(550, pot->getMsg("rmdFailed"));
}
