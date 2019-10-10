#include <vector>
#include <iostream>
#include "server_Server.h"

Server::Server(char *port, char *configFileName) :
    pot(configFileName), listener(port, &pot){
    this->listener.start();
}


void Server::run() {
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }
}
