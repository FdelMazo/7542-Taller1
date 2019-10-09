#include "server_CommandQuit.h"

std::string CommandQuit::run(std::string &dirName, bool *alive) {
    *alive = false;
    return response(221, pot->getAnswer("quitSuccess"));
}
