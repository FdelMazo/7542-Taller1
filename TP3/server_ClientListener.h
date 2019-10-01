#ifndef TP3_SERVER_CLIENTLISTENER_H
#define TP3_SERVER_CLIENTLISTENER_H

#include "common_Socket.h"
#include "common_Thread.h"
#include "server_HoneyPot.h"


class ClientListener : public Thread {
public:
    void run();

    HoneyPot *pot;
    Socket serverSkt;

    ClientListener(Socket skt, HoneyPot *pot);
};


#endif //TP3_SERVER_CLIENTLISTENER_H
