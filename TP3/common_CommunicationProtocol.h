//
// Created by delmazo on 9/30/19.
//

#ifndef TP3_COMMON_COMMUNICATIONPROTOCOL_H
#define TP3_COMMON_COMMUNICATIONPROTOCOL_H


#include "common_Socket.h"

class CommunicationProtocol {
public:
    static std::string receive(Socket skt);

    static void send(Socket skt, std::string message);
};


#endif //TP3_COMMON_COMMUNICATIONPROTOCOL_H
