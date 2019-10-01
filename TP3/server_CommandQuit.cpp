#include "server_CommandQuit.h"

std::string CommandQuit::run(std::string dirName, std::string *username, std::string *password, bool *alive) {
    *alive = false;
    return response(RC, pot->getMsg(MSG));
}
