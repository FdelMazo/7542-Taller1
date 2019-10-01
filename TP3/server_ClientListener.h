#ifndef TP3_SERVER_CLIENTLISTENER_H
#define TP3_SERVER_CLIENTLISTENER_H

#include "common_Socket.h"
#include "common_Thread.h"
#include "server_HoneyPot.h"
#include "server_ClientTalker.h"
#include <vector>


class ClientListener : public Thread {
public:
    void run();

    ~ClientListener();
    HoneyPot *pot;
    Socket serverSkt;

    ClientListener(Socket skt, HoneyPot *pot);

    std::vector<ClientTalker *> clients;
};


#endif //TP3_SERVER_CLIENTLISTENER_H
