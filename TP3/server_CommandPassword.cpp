#include "server_CommandPassword.h"

std::string CommandPassword::run(std::string passwd, std::string *username, std::string *password, bool *pBoolean) {
    *password = passwd;
    if (pot->logged(username, password)) return loginSuccessResponse();
//    return response(RC, pot->getMsg(MSG));
    return response(530, pot->getMsg("loginFailed"));

}
