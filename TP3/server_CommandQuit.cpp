#include "server_CommandQuit.h"

std::string CommandQuit::run(std::string dirName) {
    return response(221, pot->getAnswer("quitSuccess"));
}
