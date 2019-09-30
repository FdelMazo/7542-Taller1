#ifndef TP3_CLIENT_SERVERPROXY_H
#define TP3_CLIENT_SERVERPROXY_H


#include <string>
#include "common_Socket.h"

class ServerProxy {

public:
    ServerProxy(char *host, char *port);

    std::string communicate(std::string request);
    Socket skt;
};


#endif //TP3_CLIENT_SERVERPROXY_H
