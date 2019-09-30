//
// Created by delmazo on 9/30/19.
//

#ifndef TP3_SERVER_SERVER_H
#define TP3_SERVER_SERVER_H


#include <string>
#include "server_HoneyPot.h"
#include "common_Socket.h"

class Server {

public:
    Server(char *string, char *string1);

    std::string processRequest(std::string request);

    std::string receiveRequest();

    void sendResponse(std::string basicString);

    HoneyPot *pot;
    Socket skt;
    Socket clientSkt;
};


#endif //TP3_SERVER_SERVER_H
