#include <vector>
#include <iostream>
#include "server_Server.h"
#include "server_HoneyPot.h"
#include "common_Socket.h"
#include "server_ClientListener.h"

Server::Server(char *port, char *configFileName) {
    Socket serverSocket;
    serverSocket.bind(port);
    this->skt = serverSocket;
    this->pot = new HoneyPot(configFileName);
    this->listener = new ClientListener(this->skt, this->pot);
    this->listener->start();
}

void Server::run() {
    std::string input = "";
    while (input != "q") {
        std::cin >> input;
    }
}

Server::~Server() {
    delete this->pot;
    delete this->listener;
}
