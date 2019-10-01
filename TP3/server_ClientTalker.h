#ifndef TP3_SERVER_CLIENTTALKER_H
#define TP3_SERVER_CLIENTTALKER_H


#include "server_HoneyPot.h"
#include "common_Socket.h"
#include "server_Thread.h"

class ClientTalker : public Thread {

public:
    ClientTalker(HoneyPot *hpot, Socket socket);

    ~ClientTalker() override;

    void run() override;

private:
    HoneyPot *pot;
    Socket peerskt;
    std::string *user;
    std::string *passwd;

    std::string receiveRequest(Socket clientSkt);

    std::string processRequest(std::string request);

    void sendResponse(Socket clientSkt, std::string basicString);

    std::string runCommand(std::string commandName, std::string arg);
};


#endif //TP3_SERVER_CLIENTTALKER_H
