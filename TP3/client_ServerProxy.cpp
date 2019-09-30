#include "client_ServerProxy.h"

std::string ServerProxy::communicate(std::string request) {
    for(char& cReq : request) {
        this->skt.sendMsg(reinterpret_cast<const void *>(&cReq), 1);
    }
    std::string response;
    char cResp = 0;
    while(true) {
        this->skt.recvMsg(reinterpret_cast<void *>(&cResp), 1);
        response += cResp;
        if (cResp == '\n') break;
    }
    return response;
}

ServerProxy::ServerProxy(char *host, char *port) {
    Socket socket;
    socket.connection(host, port);
    this->skt = socket;
}
