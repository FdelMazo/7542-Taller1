#ifndef TP3_SERVER_COMMANDREMOVEDIR_H
#define TP3_SERVER_COMMANDREMOVEDIR_H


#include "server_Command.h"


class CommandRemoveDir : public Command {
public:
    using Command::Command;

    std::string run(std::string dirName) override;
};


#endif //TP3_SERVER_COMMANDREMOVEDIR_H
