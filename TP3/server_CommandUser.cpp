#include "server_CommandUser.h"

std::string CommandUser::run(std::string userName) {
    pot->setUser(userName);
    if (pot->logged()) return loginSuccessResponse();
    return response(RC, pot->getMsg(MSG));
}
