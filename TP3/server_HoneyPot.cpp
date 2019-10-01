#include <fstream>
#include "server_HoneyPot.h"
#include "server_Command.h"
#include <sstream>

HoneyPot::HoneyPot(const std::string configFileName) {
    std::ifstream configFile(configFileName);
    std::string key, value;
    while (std::getline(configFile, key, '=') &&
           std::getline(configFile, value)) {
        config.insert({key, value});
    }
}

std::string
HoneyPot::runCommand(std::string commandName, std::string arg, std::string *user, std::string *pass, bool *alive) {
    Command *command = Command::getCommand(commandName, this);
    if (!command)
        return Command::response(UNKNOWN_COMMAND_RC, config[UNKNOWN_COMMAND_MSG]);
    return command->run(arg, user, pass, alive);
}

bool HoneyPot::logged(std::string *username, std::string *password) {
    return (*username == config["user"] && *password == config["password"]);
}

std::set<std::string> HoneyPot::getDirList() {
    return dirList;
}

bool HoneyPot::makeDir(std::string dirName) {
    if (dirList.count(dirName))
        return false;
    dirList.insert(dirName);
    return true;
}

bool HoneyPot::rmDir(std::string dirName) {
    if (!dirList.count(dirName))
        return false;
    dirList.erase(dirName);
    return true;
}

std::string HoneyPot::getMsg(std::string command) {
    return config[command];
}
