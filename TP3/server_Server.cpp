#include <vector>
#include <sstream>
#include "server_Server.h"
#include "server_HoneyPot.h"
#include "common_Socket.h"
#include "common_CommunicationProtocol.h"

std::string Server::receiveRequest() {
    return CommunicationProtocol::receive(this->clientSkt);
}

void Server::sendResponse(std::string response) {
    return CommunicationProtocol::send(this->clientSkt, response);
}

Server::Server(char *port, char *configFileName) {
    Socket serverSocket;
    serverSocket.binding(port);
    serverSocket.listening();
    Socket clientSocket = serverSocket.acceptConnection();
    this->clientSkt = clientSocket;
    this->skt = serverSocket;
    this->pot = new HoneyPot(configFileName);
}

std::string Server::processRequest(std::string request) {
    std::istringstream stream(request);
    std::vector<std::string> command;
    std::string buff;
    while (getline(stream, buff, ' ')) {
        command.emplace_back(buff);
    }
    return pot->runCommand(command[0], command[1]);
}
