#ifndef TP3_SERVER_COMMANDLISTDIRS_H
#define TP3_SERVER_COMMANDLISTDIRS_H


#include "server_Command.h"
#include <string>
#include <mutex>

class CommandListDirs : public Command {
public:
    using Command::Command;

    std::string run(std::string &dummyArg, bool *alive) override;

    std::mutex m;
};


#endif //TP3_SERVER_COMMANDLISTDIRS_H
