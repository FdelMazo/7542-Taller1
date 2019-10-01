#include "server_CommandUser.h"

std::string CommandUser::run(std::string userName, bool *alive) {
    *username = userName;
    if (pot->validCredentials(username, password))
        return loginSuccessResponse();
    return response(331, pot->getAnswer("passRequired"));
}
