#ifndef TP3_SERVER_COMMANDUNKNOWN_H
#define TP3_SERVER_COMMANDUNKNOWN_H


#include "server_Command.h"

class CommandUnknown : public Command {
public:
    using Command::Command;

    std::string run(std::string dummyArg) override;
};

#endif //TP3_SERVER_COMMANDUNKNOWN_H
