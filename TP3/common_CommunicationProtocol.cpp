#include "common_CommunicationProtocol.h"

void CommunicationProtocol::send(Socket& skt, std::string &message) {
    message += '\0';
    for (char &c : message)
        skt.send(reinterpret_cast<const void *>(&c), 1);
}

std::string CommunicationProtocol::receive(Socket& skt) {
    std::string message;
    char c = 0;
    while (true) {
        skt.recv(reinterpret_cast<void *>(&c), 1);
        if (c == '\0') break;
        message += c;
    }
    return message;
}
