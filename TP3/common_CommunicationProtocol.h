#ifndef TP3_COMMON_COMMUNICATIONPROTOCOL_H
#define TP3_COMMON_COMMUNICATIONPROTOCOL_H


#include <string>
#include "common_Socket.h"

namespace CommunicationProtocol {
    void send(Socket skt, std::string &message);

    std::string receive(Socket skt);
}

#endif //TP3_COMMON_COMMUNICATIONPROTOCOL_H
