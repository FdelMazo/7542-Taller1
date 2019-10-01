#ifndef TP3_SERVER_COMMANDMAKEDIR_H
#define TP3_SERVER_COMMANDMAKEDIR_H


#include "server_Command.h"

class CommandMakeDir : public Command {
    static const int SUCCESS_RC = 257;
    const std::string SUCCESS_MSG = "mkdSuccess";
    static const int FAILED_RC = 550;
    const std::string FAILED_MSG = "mkdFailed";
public:
    using Command::Command;

    std::string run(std::string dirName, std::string *username, std::string *password, bool *pBoolean);
};


#endif //TP3_SERVER_COMMANDMAKEDIR_H
