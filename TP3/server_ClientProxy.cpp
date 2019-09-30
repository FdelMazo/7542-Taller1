#include "server_ClientProxy.h"

ClientProxy::ClientProxy(char *port) {
    Socket serverSocket;
    serverSocket.binding(port);
    serverSocket.listening();
    Socket clientSkt = serverSocket.acceptConnection();
    this->serverSkt = serverSocket;
    this->skt = clientSkt;
}

std::string ClientProxy::communicate() {
    std::string request;
    char cResp = 0;
    while(true) {
        this->skt.recvMsg(reinterpret_cast<void *>(&cResp), 1);
        if (cResp == '\n') break;
        request += cResp;
    }
    return request;
}

void ClientProxy::communicate(std::string response) {
    for(char& cReq : response) {
        this->skt.sendMsg(reinterpret_cast<const void *>(&cReq), 1);
    }
}
