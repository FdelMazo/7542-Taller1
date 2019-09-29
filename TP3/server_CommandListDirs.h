#ifndef TP3_SERVER_COMMANDLISTDIRS_H
#define TP3_SERVER_COMMANDLISTDIRS_H


#include "server_Command.h"

class CommandListDirs : public Command {
    const std::string DUMMY_LS = "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34";

    const int BEGIN_RC = 150;
    const std::string BEGIN_MSG = "listBegin";
    const int END_RC = 226;
    const std::string END_MSG = "listEnd";
public:
    using Command::Command;

    std::string run(std::string dummyArg) override;
};


#endif //TP3_SERVER_COMMANDLISTDIRS_H
