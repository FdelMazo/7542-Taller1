#ifndef TP3_SERVER_COMMANDQUIT_H
#define TP3_SERVER_COMMANDQUIT_H


#include "server_Command.h"

class CommandQuit : public Command {
    static const int RC = 221;
    const std::string MSG = "quitSuccess";
public:
    using Command::Command;

    std::string run(std::string dummyArg, std::string *username, std::string *password, bool *pBoolean) override;
};


#endif //TP3_SERVER_COMMANDQUIT_H
