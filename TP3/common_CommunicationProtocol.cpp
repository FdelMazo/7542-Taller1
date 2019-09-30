//
// Created by delmazo on 9/30/19.
//

#include "common_CommunicationProtocol.h"

std::string CommunicationProtocol::receive(Socket skt) {
    std::string message;
    char c = 0;
    while (c != '\n') {
        skt.recvMsg(reinterpret_cast<void *>(&c), 1);
        message += c;
    }
    return message;
}

void CommunicationProtocol::send(Socket skt, std::string message) {
    for (char &c : message) {
        skt.sendMsg(reinterpret_cast<const void *>(&c), 1);
    }
}
