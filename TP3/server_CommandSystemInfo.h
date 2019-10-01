#ifndef TP3_SERVER_COMMANDSYSTEMINFO_H
#define TP3_SERVER_COMMANDSYSTEMINFO_H


#include "server_Command.h"

class CommandSystemInfo : public Command {
    static const int RC = 215;
    const std::string MSG = "systemInfo";
public:
    using Command::Command;

    std::string run(std::string dummyArg, std::string *username, std::string *password, bool *pBoolean);
};


#endif //TP3_SERVER_COMMANDSYSTEMINFO_H
