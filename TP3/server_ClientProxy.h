#ifndef TP3_SERVER_CLIENTPROXY_H
#define TP3_SERVER_CLIENTPROXY_H


#include <string>
#include "common_Socket.h"

class ClientProxy {
public:
    ClientProxy(char *port);

    std::string communicate();
    Socket serverSkt;

    void communicate(std::string response);

    Socket skt;
};


#endif //TP3_SERVER_CLIENTPROXY_H
