#ifndef TP3_SERVER_COMMANDPASSWORD_H
#define TP3_SERVER_COMMANDPASSWORD_H


#include "server_Command.h"

class CommandPassword : public Command {
    static const int RC = 530;
    const std::string MSG = "loginFailed";
public:
    using Command::Command;

    std::string run(std::string passwd, std::string *username, std::string *password, bool *pBoolean) override;
};


#endif //TP3_SERVER_COMMANDPASSWORD_H
