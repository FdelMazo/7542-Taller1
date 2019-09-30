#include "client_Client.h"
#include "common_CommunicationProtocol.h"

Client::Client(char *host, char *port) {
    Socket socket;
    socket.connection(host, port);
    this->skt = socket;
}

void Client::sendRequest(std::string request) {
    CommunicationProtocol::send(this->skt, request);
}

std::string Client::getResponse() {
    return CommunicationProtocol::receive(this->skt);
}
