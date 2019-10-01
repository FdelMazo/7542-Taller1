#ifndef TP3_COMMON_COMMUNICATIONPROTOCOL_H
#define TP3_COMMON_COMMUNICATIONPROTOCOL_H


#include "common_Socket.h"

namespace CommunicationProtocol {
    std::string receive(Socket skt);

    void send(Socket skt, std::string message);
}


#endif //TP3_COMMON_COMMUNICATIONPROTOCOL_H
