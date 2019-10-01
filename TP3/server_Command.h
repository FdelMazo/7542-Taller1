#ifndef TP3_SERVER_COMMAND_H
#define TP3_SERVER_COMMAND_H


#include <bits/unique_ptr.h>
#include "server_HoneyPot.h"

class Command {
    static const int NOT_LOGGED_RC;
    static const char NOT_LOGGED_MSG[];

    static const int LOGIN_RC;
    static const char LOGIN_MSG[];

    static const int NEW_CLIENT_RC;
    static const char NEW_CLIENT_MSG[];

public:
    explicit Command(HoneyPot *pot, std::string *user, std::string *pass);

    virtual std::string run(std::string arg) = 0;

    static std::unique_ptr<Command> getCommand(std::string command,
                                               HoneyPot *pot, std::string *user, std::string *pass);

    static std::string response(int retCode, std::string message);

    static std::string response(int retCode, std::string message,
                                std::string argument);

    static std::string acceptClient(HoneyPot *pot);

protected:
    std::string notLoggedResponse();
    std::string loginSuccessResponse();

    HoneyPot *pot;
    std::string *username;
    std::string *password;
};


#endif //TP3_SERVER_COMMAND_H
