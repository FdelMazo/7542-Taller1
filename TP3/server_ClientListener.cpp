#include <iostream>
#include "server_ClientListener.h"

void ClientListener::run() {
    while (true) {
        Socket clientSkt = this->serverSkt.accept();
        std::cerr << "New Client!\n";
        ClientTalker *client = new ClientTalker(this->pot, clientSkt);
        clients.push_back(client);
        client->start();
    }
}

ClientListener::ClientListener(Socket skt, HoneyPot *hpot) {
    this->pot = hpot;
    this->serverSkt = skt;
    this->serverSkt.listen();
}

ClientListener::~ClientListener() {
    for (ClientTalker *c : clients) {
        delete c;
    }
    this->join();
}
