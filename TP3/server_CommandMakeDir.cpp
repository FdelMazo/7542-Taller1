#include "server_CommandMakeDir.h"

std::string CommandMakeDir::run(std::string dirName) {
    if (!pot->logged()) return notLoggedResponse();
    if (pot->makeDir(dirName))
        return response(SUCCESS_RC, pot->getMsg(SUCCESS_MSG), dirName);
    return response(FAILED_RC, pot->getMsg(FAILED_MSG));
}
