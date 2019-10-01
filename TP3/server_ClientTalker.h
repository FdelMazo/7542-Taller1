#ifndef TP3_SERVER_CLIENTTALKER_H
#define TP3_SERVER_CLIENTTALKER_H


#include "server_Server.h"

class ClientTalker : public Thread {

public:
    ClientTalker(HoneyPot *hpot, Socket socket);

    std::string processRequest(std::string request);

    std::string receiveRequest(Socket clientSkt);

    void sendResponse(Socket clientSkt, std::string basicString);

    void run();

    HoneyPot *pot;
    Socket skt;
    std::string *username;
    std::string *password;
};


#endif //TP3_SERVER_CLIENTTALKER_H
