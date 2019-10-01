#include <vector>
#include <iostream>
#include "server_Server.h"

Server::Server(char *port, char *configFileName) {
    this->pot = new HoneyPot(configFileName);
    this->listener = new ClientListener(port, this->pot);
    this->listener->start();
}

Server::~Server() {
    delete this->pot;
    delete this->listener;
}

void Server::run() {
    std::string input;
    while (input != "q") {
        std::cin >> input;
    }
}
