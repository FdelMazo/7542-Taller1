#ifndef TP3_CLIENT_CLIENT_H
#define TP3_CLIENT_CLIENT_H


#include <string>
#include "common_Socket.h"

class Client {

public:
    Client(char *host, char *port);

    void run();

private:
    Socket skt;
    void sendRequest(std::string request);
    std::string getResponse();
};


#endif //TP3_CLIENT_CLIENT_H
