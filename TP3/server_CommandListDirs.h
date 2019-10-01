#ifndef TP3_SERVER_COMMANDLISTDIRS_H
#define TP3_SERVER_COMMANDLISTDIRS_H


#include "server_Command.h"

class CommandListDirs : public Command {
public:
    using Command::Command;

    std::string run(std::string dummyArg) override;
};


#endif //TP3_SERVER_COMMANDLISTDIRS_H
