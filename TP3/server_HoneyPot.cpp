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
HoneyPot::runCommand(std::string commandName, std::string arg,
                     std::string *user, std::string *pass, bool *alive) {
    std::unique_ptr<Command> command =
            Command::getCommand(commandName, this);
    if (!command)
        return Command::response(UNKNOWN_COMMAND_RC,
                                 config[UNKNOWN_COMMAND_MSG]);
    return command->run(arg, user, pass, alive);
}

bool HoneyPot::logged(std::string *username, std::string *password) {
    return (*username == config["user"] && *password == config["password"]);
}

std::set<std::string> HoneyPot::getDirList() {
    return dirList.get();
}

bool HoneyPot::makeDir(std::string dirName) {
    return dirList.mkDir(dirName);
}

bool HoneyPot::rmDir(std::string dirName) {
    return dirList.rmDir(dirName);
}

std::string HoneyPot::getMsg(std::string command) {
    return config[command];
}

std::string HoneyPot::acceptClient() {
    return Command::response(NEW_CLIENT_RC, config[NEW_CLIENT_MSG]);
}
