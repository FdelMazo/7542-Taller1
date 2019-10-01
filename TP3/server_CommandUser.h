#ifndef TP3_SERVER_COMMANDUSER_H
#define TP3_SERVER_COMMANDUSER_H


#include "server_Command.h"

class CommandUser : public Command {
public:
    using Command::Command;

    std::string run(std::string userName) override;
};


#endif //TP3_SERVER_COMMANDUSER_H
