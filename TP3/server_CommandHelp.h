#ifndef TP3_SERVER_COMMANDHELP_H
#define TP3_SERVER_COMMANDHELP_H


#include "server_Command.h"

class CommandHelp : public Command {
public:
    using Command::Command;

    std::string run(std::string dummyArg) override;
};


#endif //TP3_SERVER_COMMANDHELP_H
