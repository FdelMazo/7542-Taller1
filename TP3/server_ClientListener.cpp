#include <iostream>
#include "server_ClientListener.h"

ClientListener::ClientListener(char *port, HoneyPot *hpot) {
    Socket serverSocket;
    serverSocket.bind(port);
    this->pot = hpot;
    this->serverSkt = std::move(serverSocket);
    this->serverSkt.listen();
}

ClientListener::~ClientListener() {
    for (ClientTalker *c : clients) {
        delete c;
    }
    this->serverSkt.close();
    this->join();
}

void ClientListener::run() {
    while (true) {
        Socket clientSkt;
        try {
            clientSkt = this->serverSkt.accept();
        }
        catch (std::invalid_argument) {
            break;
        }
        std::cerr << "New Client!\n";
        ClientTalker *client = new ClientTalker(this->pot,
                std::move(clientSkt));
        clients.push_back(client);
        client->start();
    }
}
