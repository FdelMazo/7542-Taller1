#ifndef TP3_CLIENT_CLIENT_H
#define TP3_CLIENT_CLIENT_H


#include <string>
#include "common_Socket.h"

class Client {

public:
    Client(char *host, char *port);

    void sendRequest(std::string request);
    Socket skt;

    std::string getResponse();

    void run();
};


#endif //TP3_CLIENT_CLIENT_H
