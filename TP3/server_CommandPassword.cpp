#include "server_CommandPassword.h"

std::string CommandPassword::run(std::string passwd) {
    *password = passwd;
    if (pot->validCredentials(username, password))
        return loginSuccessResponse();
    return response(530, pot->getAnswer("loginFailed"));
}
