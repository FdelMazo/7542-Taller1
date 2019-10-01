#ifndef TP3_SERVER_COMMANDREMOVEDIR_H
#define TP3_SERVER_COMMANDREMOVEDIR_H


#include "server_Command.h"


class CommandRemoveDir : public Command {
//    static const int SUCCESS_RC = 250;
//    const std::string SUCCESS_MSG = "rmdSuccess";
//    static const int FAILED_RC = 550;
//    const std::string FAILED_MSG = "rmdFailed";

public:
    using Command::Command;

    std::string run(std::string dirName, std::string *username, std::string *password, bool *pBoolean);
};


#endif //TP3_SERVER_COMMANDREMOVEDIR_H
