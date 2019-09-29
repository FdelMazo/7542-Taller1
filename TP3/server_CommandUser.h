#ifndef TP3_SERVER_COMMANDUSER_H
#define TP3_SERVER_COMMANDUSER_H


#include "server_Command.h"

class CommandUser : public Command {
    const int RC = 331;
    const std::string MSG = "passRequired";

public:
    using Command::Command;

    std::string run(std::string userName);
};


#endif //TP3_SERVER_COMMANDUSER_H
