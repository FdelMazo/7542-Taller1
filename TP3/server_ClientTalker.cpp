#include <vector>
#include <sstream>
#include "server_ClientTalker.h"
#include "common_CommunicationProtocol.h"

std::string ClientTalker::receiveRequest(Socket clientSkt) {
    return CommunicationProtocol::receive(clientSkt);
}

std::string ClientTalker::processRequest(std::string request) {
    std::istringstream stream(request);
    std::vector<std::string> command;
    std::string buff;
    while (getline(stream, buff, ' ')) {
        command.emplace_back(buff);
    }
    return pot->runCommand(command[0], command[1]);
}

void ClientTalker::sendResponse(Socket clientSkt, std::string response) {
    return CommunicationProtocol::send(clientSkt, response);
}


ClientTalker::ClientTalker(HoneyPot *hpot, Socket socket) {
    this->pot = hpot;
    this->skt = socket;
}

void ClientTalker::run() {
    std::string request = receiveRequest(this->skt);
    std::string response = processRequest(request);
    sendResponse(this->skt, response);
}
