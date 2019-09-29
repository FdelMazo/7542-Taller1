#include "server_CommandPassword.h"

std::string CommandPassword::run(std::string passwd) {
    pot->setPasswd(passwd);
    if (pot->logged()) return loginSuccessResponse();
    return response(RC, pot->getMsg(MSG));
}
