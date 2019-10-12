#ifndef TP3_SERVER_CLIENTLISTENER_H
#define TP3_SERVER_CLIENTLISTENER_H

#include "common_Socket.h"
#include "server_Thread.h"
#include "server_HoneyPot.h"
#include "server_ClientTalker.h"
#include <list>


class ClientListener : public Thread {
public:
    ClientListener(char *skt, HoneyPot *pot);

    ~ClientListener() override;

    void run() override;

private:
    HoneyPot *pot;
    Socket serverSkt;
    std::list<ClientTalker *> clients;

    void garbageCollector();
};


#endif //TP3_SERVER_CLIENTLISTENER_H
