#include <algorithm>
#include "common_CommunicationProtocol.h"

std::string CommunicationProtocol::receive(Socket skt) {
    std::string message;
    char c = 0;
    while (true) {
        skt.recvMsg(reinterpret_cast<void *>(&c), 1);
        if (c == '\n') break;
        message += c;
    }
    std::replace(message.begin(), message.end(), '\t', '\n');
    return message;
}

void CommunicationProtocol::send(Socket skt, std::string message) {
    for (char &c : message) {
        skt.sendMsg(reinterpret_cast<const void *>(&c), 1);
    }
}
