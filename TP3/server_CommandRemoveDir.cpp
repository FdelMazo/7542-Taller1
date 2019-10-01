#include "server_CommandRemoveDir.h"

std::string CommandRemoveDir::run(std::string dirName, std::string *username, std::string *password) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    if (pot->rmDir(dirName))
        return response(SUCCESS_RC, pot->getMsg(SUCCESS_MSG));
    return response(FAILED_RC, pot->getMsg(FAILED_MSG));
}
