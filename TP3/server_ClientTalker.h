#ifndef TP3_SERVER_CLIENTTALKER_H
#define TP3_SERVER_CLIENTTALKER_H


#include "server_HoneyPot.h"
#include "common_Socket.h"
#include "server_Thread.h"
#include <string>

class ClientTalker : public Thread {
public:
    ClientTalker(HoneyPot *hpot, Socket socket);

    ~ClientTalker() override;

    void run() override;

    bool isAlive();

private:
    HoneyPot *pot;
    Socket peerskt;
    std::string user = "";
    std::string passwd = "";
    bool alive = true;

    std::string receiveRequest();

    std::string processRequest(std::string &request);

    void sendResponse(std::string &basicString);

    std::string runCommand(std::string &commandName, std::string &arg);
};


#endif //TP3_SERVER_CLIENTTALKER_H
