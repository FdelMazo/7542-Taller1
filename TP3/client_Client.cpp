#include <iostream>
#include "client_Client.h"
#include "common_CommunicationProtocol.h"

Client::Client(char *host, char *port) {
    Socket socket;
    socket.connect(host, port);
    this->skt = socket;
}

void Client::sendRequest(std::string request) {
    CommunicationProtocol::send(this->skt, request);
}

std::string Client::getResponse() {
    return CommunicationProtocol::receive(this->skt);
}

void Client::run() {
    while (true) {
        std::string request;
        getline(std::cin, request);
        sendRequest(request);
        std::string response = getResponse();
        std::cout << response;
    }
}
