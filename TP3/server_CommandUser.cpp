#include "server_CommandUser.h"

std::string CommandUser::run(std::string userName,
                             std::string *username, std::string *password, bool *pBoolean) {
    *username = userName;
    if (pot->logged(username, password)) return loginSuccessResponse();
    return response(RC, pot->getMsg(MSG));
}
