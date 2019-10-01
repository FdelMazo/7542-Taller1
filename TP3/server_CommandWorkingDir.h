#ifndef TP3_SERVER_COMMANDWORKINGDIR_H
#define TP3_SERVER_COMMANDWORKINGDIR_H


#include "server_Command.h"

class CommandWorkingDir : public Command {
//    const int RC = 257;
//    const std::string MSG = "currentDirectoryMsg";
public:
    using Command::Command;

    std::string run(std::string dummyArg, std::string *username, std::string *password, bool *pBoolean);
};


#endif //TP3_SERVER_COMMANDWORKINGDIR_H
