#include "common_CommunicationProtocol.h"

std::string CommunicationProtocol::receive(Socket skt) {
    std::string message;
    char c = 0;
    while (true) {
        skt.recvMsg(reinterpret_cast<void *>(&c), 1);
        if (c == '\0') break;
        message += c;
    }
    return message;
}

void CommunicationProtocol::send(Socket skt, std::string message) {
    message += '\0';
    for (char &c : message) {
        skt.sendMsg(reinterpret_cast<const void *>(&c), 1);
    }
}
