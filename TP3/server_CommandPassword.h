#ifndef TP3_SERVER_COMMANDPASSWORD_H
#define TP3_SERVER_COMMANDPASSWORD_H


#include "server_Command.h"

class CommandPassword : public Command {
    const int RC = 530;
    const std::string MSG = "loginFailed";
public:
    using Command::Command;

    std::string run(std::string passwd) override;
};


#endif //TP3_SERVER_COMMANDPASSWORD_H
