#ifndef TP3_SERVER_COMMANDMAKEDIR_H
#define TP3_SERVER_COMMANDMAKEDIR_H


#include "server_Command.h"
#include <string>

class CommandMakeDir : public Command {
public:
    using Command::Command;

    std::string run(std::string &dirName, bool *alive) override;
};


#endif //TP3_SERVER_COMMANDMAKEDIR_H
