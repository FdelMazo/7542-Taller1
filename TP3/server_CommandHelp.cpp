#include "server_CommandHelp.h"

std::string CommandHelp::run(std::string dummyArg) {
    if (!pot->logged()) return notLoggedResponse();
    return response(RC, pot->getMsg(MSG));
}
