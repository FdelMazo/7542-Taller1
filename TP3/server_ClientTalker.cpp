#include <vector>
#include <sstream>
#include <iostream>
#include "server_ClientTalker.h"
#include "common_CommunicationProtocol.h"
#include "server_Command.h"

ClientTalker::ClientTalker(HoneyPot *hpot, Socket socket) {
    this->pot = hpot;
    this->peerskt = std::move(socket);
}

ClientTalker::~ClientTalker() {
    this->peerskt.close();
    this->join();
}

void ClientTalker::run() {
    std::string greeting = Command::acceptClient(this->pot);
    sendResponse(greeting);
    while (this->alive) {
        std::string request = receiveRequest();
        if (request.empty()) {
            this->alive = false;
            break;
        }
        std::string response = processRequest(request);
        sendResponse(response);
    }
    std::cerr << "Farewell Client!\n";
}

std::string ClientTalker::receiveRequest() {
    return CommunicationProtocol::receive(this->peerskt);
}

std::string ClientTalker::processRequest(std::string &request) {
    std::istringstream stream(request);
    std::string command;
    std::getline(stream, command, ' ');
    std::string arg;
    std::getline(stream, arg);
    if (arg.empty()) arg = "";
    return runCommand(command, arg);
}

void ClientTalker::sendResponse(std::string &basicString) {
    return CommunicationProtocol::send(this->peerskt, basicString);
}


std::string ClientTalker::runCommand(std::string &commandName,
        std::string &arg) {
    std::unique_ptr<Command> command =
            Command::getCommand(commandName,
                                this->pot, this->user, this->passwd);
    return command->run(arg, &this->alive);
}
