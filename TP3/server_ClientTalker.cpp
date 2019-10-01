#include <vector>
#include <sstream>
#include <iostream>
#include "server_ClientTalker.h"
#include "common_CommunicationProtocol.h"
#include "server_Command.h"

ClientTalker::ClientTalker(HoneyPot *hpot, Socket socket) {
    this->pot = hpot;
    this->peerskt = socket;
    this->alive = new bool(true);
    this->user = new std::string("");
    this->passwd = new std::string("");
}

ClientTalker::~ClientTalker() {
    delete this->user;
    delete this->passwd;
    delete this->alive;
    this->peerskt.close();
    this->join();
}

void ClientTalker::run() {
    std::string greeting = Command::acceptClient(this->pot);
    sendResponse(this->peerskt, greeting);
    while (*this->alive) {
        std::string request = receiveRequest(this->peerskt);
        if (request.empty()) {
            *this->alive = false;
            break;
        }
        std::string response = processRequest(request);
        sendResponse(this->peerskt, response);
    }
    std::cerr << "Farewell Client!\n";
}

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
    return runCommand(command, arg);
}

void ClientTalker::sendResponse(Socket clientSkt, std::string response) {
    return CommunicationProtocol::send(clientSkt, response);
}


std::string ClientTalker::runCommand(std::string commandName, std::string arg) {
    std::unique_ptr<Command> command =
            Command::getCommand(commandName,
                                this->pot, this->user, this->passwd);
    return command->run(arg, this->alive);
}
