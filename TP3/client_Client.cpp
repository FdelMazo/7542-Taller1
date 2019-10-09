#include <iostream>
#include "client_Client.h"
#include "common_CommunicationProtocol.h"

Client::Client(char *host, char *port) {
    this->skt.connect(host, port);
}

void Client::run() {
    std::string greeting = getResponse();
    std::cout << greeting;
    while (true) {
        std::string request;
        std::getline(std::cin, request);
        if (request.empty()) break;
        sendRequest(request);
        std::string response = getResponse();
        if (response.empty()) break;
        std::cout << response;
    }
}

void Client::sendRequest(std::string &request) {
    CommunicationProtocol::send(this->skt, request);
}

std::string Client::getResponse() {
    return CommunicationProtocol::receive(this->skt);
}
