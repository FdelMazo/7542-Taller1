#include "server_CommandSystemInfo.h"

std::string CommandSystemInfo::run(std::string dummyArg) {
    if (!pot->logged()) return notLoggedResponse();
    return response(RC, pot->getMsg(MSG));
}
