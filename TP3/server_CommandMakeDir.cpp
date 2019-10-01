#include "server_CommandMakeDir.h"

std::string CommandMakeDir::run(std::string dirName, std::string *username, std::string *password, bool *pBoolean) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    if (pot->makeDir(dirName))
        return response(257, pot->getMsg("mkdSuccess"), dirName);
//        return response(SUCCESS_RC, pot->getMsg(SUCCESS_MSG), dirName);
//    return response(FAILED_RC, pot->getMsg(FAILED_MSG));
    return response(550, pot->getMsg("mkdFailed"));
}
