#include "server_CommandWorkingDir.h"

std::string CommandWorkingDir::run(std::string dummyArg) {
    if (!pot->logged()) return notLoggedResponse();
    return response(RC, pot->getMsg(MSG));
}
