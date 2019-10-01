#include <sstream>
#include "server_Command.h"
#include "server_CommandUser.h"
#include "server_CommandListDirs.h"
#include "server_CommandMakeDir.h"
#include "server_CommandRemoveDir.h"
#include "server_CommandHelp.h"
#include "server_CommandPassword.h"
#include "server_CommandWorkingDir.h"
#include "server_CommandSystemInfo.h"
#include "server_CommandQuit.h"

Command::Command(HoneyPot *pot) {
    this->pot = pot;
}

std::unique_ptr<Command> Command::getCommand(std::string command,
                                             HoneyPot *pot) {
    if (command == "USER")
        return std::unique_ptr<Command>(new CommandUser(pot));
    else if (command == "PASS")
        return std::unique_ptr<Command>(new CommandPassword(pot));
    else if (command == "SYST")
        return std::unique_ptr<Command>(new CommandSystemInfo(pot));
    else if (command == "LIST")
        return std::unique_ptr<Command>(new CommandListDirs(pot));
    else if (command == "HELP")
        return std::unique_ptr<Command>(new CommandHelp(pot));
    else if (command == "PWD")
        return std::unique_ptr<Command>(new CommandWorkingDir(pot));
    else if (command == "MKD")
        return std::unique_ptr<Command>(new CommandMakeDir(pot));
    else if (command == "RMD")
        return std::unique_ptr<Command>(new CommandRemoveDir(pot));
    else if (command == "QUIT")
        return std::unique_ptr<Command>(new CommandQuit(pot));
    return nullptr;
}

std::string Command::notLoggedResponse() {
    return response(NOT_LOGGED_RC, pot->getMsg(NOT_LOGGED_MSG));
}

std::string Command::loginSuccessResponse() {
    return response(LOGIN_RC, pot->getMsg(LOGIN_MSG));
}

std::string Command::response(int retCode, std::string message) {
    std::ostringstream stream;
    stream << retCode << " " << message << "\n";
    return stream.str();
}

std::string Command::response(int retCode, std::string message,
                              std::string argument) {
    std::ostringstream stream;
    stream << retCode << " " << argument << " " << message << "\n";
    return stream.str();
}
