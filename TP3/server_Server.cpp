#include <vector>
#include <sstream>
#include "server_Server.h"
#include "server_HoneyPot.h"
#include "common_Socket.h"
#include "server_ClientListener.h"

Server::Server(char *port, char *configFileName) {
    Socket serverSocket;
    serverSocket.binding(port);
    this->skt = serverSocket;
    this->pot = new HoneyPot(configFileName);
    this->listener = new ClientListener(this->skt, this->pot);
}

void Server::communicate() {
    this->listener->start();
}
