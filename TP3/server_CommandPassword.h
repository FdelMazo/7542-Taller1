#ifndef TP3_SERVER_COMMANDPASSWORD_H
#define TP3_SERVER_COMMANDPASSWORD_H


#include "server_Command.h"
#include <string>

class CommandPassword : public Command {
public:
    using Command::Command;

    std::string run(std::string &passwd, bool *alive) override;
};


#endif //TP3_SERVER_COMMANDPASSWORD_H
