#include <iostream>
#include "server_ClientListener.h"
#include "server_ClientTalker.h"

void ClientListener::run() {
    while (true) {
        Socket clientSkt = this->serverSkt.acceptConnection();
        std::cerr << "New Client!\n";
        ClientTalker *client = new ClientTalker(this->pot, clientSkt);
        client->start();
    }
}

ClientListener::ClientListener(Socket skt, HoneyPot *hpot) {
    this->pot = hpot;
    this->serverSkt = skt;
    this->serverSkt.listening();
}
