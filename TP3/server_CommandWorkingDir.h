#ifndef TP3_SERVER_COMMANDWORKINGDIR_H
#define TP3_SERVER_COMMANDWORKINGDIR_H


#include "server_Command.h"

class CommandWorkingDir : public Command {
public:
    using Command::Command;

    std::string run(std::string dummyArg) override;
};


#endif //TP3_SERVER_COMMANDWORKINGDIR_H
