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

Command::Command(HoneyPot *pot) {
    this->pot = pot;
}

Command *Command::getCommand(std::string command, HoneyPot *pot) {
    if (command == "USER")
        return new CommandUser(pot);
    else if (command == "PASS")
        return new CommandPassword(pot);
    else if (command == "SYST")
        return new CommandSystemInfo(pot);
    else if (command == "LIST")
        return new CommandListDirs(pot);
    else if (command == "HELP")
        return new CommandHelp(pot);
    else if (command == "PWD")
        return new CommandWorkingDir(pot);
    else if (command == "MKD")
        return new CommandMakeDir(pot);
    else if (command == "RMD")
        return new CommandRemoveDir(pot);
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
