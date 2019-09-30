#ifndef TP3_SERVER_COMMANDHELP_H
#define TP3_SERVER_COMMANDHELP_H


#include "server_Command.h"

class CommandHelp : public Command {
    static const int RC = 214;
    const std::string MSG = "commands";
public:
    using Command::Command;

    std::string run(std::string dummyArg) override;
};


#endif //TP3_SERVER_COMMANDHELP_H
