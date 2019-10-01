#ifndef TP3_SERVER_SERVER_H
#define TP3_SERVER_SERVER_H


#include <string>
#include "server_HoneyPot.h"
#include "common_Socket.h"
#include "server_ClientListener.h"


class Server {

public:
    Server(char *string, char *string1);

    HoneyPot *pot;
    Socket skt;
    ClientListener *listener;

    void communicate();
};


#endif //TP3_SERVER_SERVER_H
