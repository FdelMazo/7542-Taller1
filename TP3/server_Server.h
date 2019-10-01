#ifndef TP3_SERVER_SERVER_H
#define TP3_SERVER_SERVER_H


#include <string>
#include "server_HoneyPot.h"
#include "server_ClientListener.h"

class Server {
public:
    Server(char *string, char *string1);

    ~Server();

    void run();

private:
    HoneyPot *pot;
    ClientListener *listener;
};


#endif //TP3_SERVER_SERVER_H
