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
    if (command.size() == 1) command.emplace_back("");
    return pot->runCommand(command[0], command[1], this->username, this->password);
}

void ClientTalker::sendResponse(Socket clientSkt, std::string response) {
    return CommunicationProtocol::send(clientSkt, response);
}


ClientTalker::ClientTalker(HoneyPot *hpot, Socket socket) {
    this->pot = hpot;
    this->skt = socket;
    this->username = new std::string;
    this->password = new std::string;
}

void ClientTalker::run() {
    while (true) {
        std::string request = receiveRequest(this->skt);
        std::string response = processRequest(request);
        sendResponse(this->skt, response);
    }
}
