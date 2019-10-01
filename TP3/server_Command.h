#ifndef TP3_SERVER_COMMAND_H
#define TP3_SERVER_COMMAND_H


#include "server_HoneyPot.h"

class Command {
    static const int NOT_LOGGED_RC = 530;
    const std::string NOT_LOGGED_MSG = "clientNotLogged";

    static const int LOGIN_RC = 230;
    const std::string LOGIN_MSG = "loginSuccess";

    static const int UNKNOWN_COMMAND_RC = 500;
    const std::string UNKNOWN_COMMAND_MSG = "unknownCommand";
protected:
    HoneyPot *pot;

public:
    explicit Command(HoneyPot *pot);

    virtual std::string run(std::string arg, std::string *username, std::string *password) = 0;

    std::string notLoggedResponse();

    std::string loginSuccessResponse();

    static Command *getCommand(std::string command, HoneyPot *pot);

    static std::string response(int retCode, std::string message, std::string argument);

    static std::string response(int retCode, std::string message);

};


#endif //TP3_SERVER_COMMAND_H
