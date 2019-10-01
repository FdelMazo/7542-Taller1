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
#include "server_CommandUnknown.h"

const int Command::NOT_LOGGED_RC = 530;
const char Command::NOT_LOGGED_MSG[] = "clientNotLogged";
const int Command::LOGIN_RC = 230;
const char Command::LOGIN_MSG[] = "loginSuccess";
const int Command::NEW_CLIENT_RC = 220;
const char Command::NEW_CLIENT_MSG[] = "newClient";

Command::Command(HoneyPot *pot, std::string *user, std::string *pass) {
    this->pot = pot;
    this->username = user;
    this->password = pass;
}

std::unique_ptr<Command>
Command::getCommand(std::string command, HoneyPot *pot,
                    std::string *user, std::string *pass) {
    if (command == "USER")
        return std::unique_ptr<Command>(new CommandUser(pot, user, pass));
    else if (command == "PASS")
        return std::unique_ptr<Command>(new CommandPassword(pot, user, pass));
    else if (command == "QUIT")
        return std::unique_ptr<Command>(new CommandQuit(pot, user, pass));
    else if (command == "SYST")
        return std::unique_ptr<Command>(new CommandSystemInfo(pot, user, pass));
    else if (command == "LIST")
        return std::unique_ptr<Command>(new CommandListDirs(pot, user, pass));
    else if (command == "HELP")
        return std::unique_ptr<Command>(new CommandHelp(pot, user, pass));
    else if (command == "PWD")
        return std::unique_ptr<Command>(new CommandWorkingDir(pot, user, pass));
    else if (command == "MKD")
        return std::unique_ptr<Command>(new CommandMakeDir(pot, user, pass));
    else if (command == "RMD")
        return std::unique_ptr<Command>(new CommandRemoveDir(pot, user, pass));
    return std::unique_ptr<Command>(new CommandUnknown(pot, user, pass));;
}

std::string Command::response(int retCode, std::string message) {
    std::ostringstream stream;
    stream << retCode << " " << message << "\n";
    return stream.str();
}

std::string Command::response(int retCode, std::string message,
                              std::string argument) {
    std::ostringstream stream;
    stream << retCode << " \"" << argument << "\" " << message << "\n";
    return stream.str();
}

std::string Command::acceptClient(HoneyPot *pot) {
    return Command::response(NEW_CLIENT_RC, pot->getAnswer(NEW_CLIENT_MSG));
}

std::string Command::notLoggedResponse() {
    return response(NOT_LOGGED_RC, pot->getAnswer(NOT_LOGGED_MSG));
}

std::string Command::loginSuccessResponse() {
    return response(LOGIN_RC, pot->getAnswer(LOGIN_MSG));
}
