#ifndef TP3_SERVER_COMMANDWORKINGDIR_H
#define TP3_SERVER_COMMANDWORKINGDIR_H


#include "server_Command.h"
#include <string>

class CommandWorkingDir : public Command {
public:
    using Command::Command;

    std::string run(std::string dummyArg, bool *alive) override;
};


#endif //TP3_SERVER_COMMANDWORKINGDIR_H
