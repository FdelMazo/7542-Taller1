#include <vector>
#include <sstream>
#include <iostream>
#include "server_ClientTalker.h"
#include "common_CommunicationProtocol.h"

std::string ClientTalker::receiveRequest(Socket clientSkt) {
    return CommunicationProtocol::receive(clientSkt);
}

std::string ClientTalker::processRequest(std::string request) {
    std::istringstream stream(request);
    std::string command;
    std::getline(stream, command, ' ');
    std::string arg;
    std::getline(stream, arg);
    if (arg.empty()) arg = "";
    return pot->runCommand(command, arg, this->username, this->password, this->alive);
}

void ClientTalker::sendResponse(Socket clientSkt, std::string response) {
    return CommunicationProtocol::send(clientSkt, response);
}


ClientTalker::ClientTalker(HoneyPot *hpot, Socket socket) {
    this->pot = hpot;
    this->skt = socket;
    this->alive = new bool(true);
    this->username = new std::string("");
    this->password = new std::string("");
}

void ClientTalker::run() {
    std::string greeting = this->pot->acceptClient();
    sendResponse(this->skt, greeting);
    while (*alive) {
        std::string request = receiveRequest(this->skt);
        if (request.empty()) {
            *alive = false;
            break;
        }
        std::string response = processRequest(request);
        sendResponse(this->skt, response);
    }
    std::cerr << "Farewell Client!\n";
}

ClientTalker::~ClientTalker() {
    delete this->alive;
    delete this->username;
    delete this->password;
    this->skt.close();
    this->join();
}
