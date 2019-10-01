#include "server_HoneyPot.h"
#include <fstream>
#include <sstream>

HoneyPot::HoneyPot(const std::string configFileName) {
    std::ifstream configFile(configFileName);
    std::string key, value;
    while (std::getline(configFile, key, '=') &&
           std::getline(configFile, value)) {
        config.insert({key, value});
    }
}

std::string HoneyPot::getAnswer(std::string command) {
    return config[command];
}

bool HoneyPot::validCredentials(std::string *username, std::string *password) {
    return (*username == config["user"] && *password == config["password"]);
}

bool HoneyPot::mkDir(std::string dirName) {
    return dirList.addDir(dirName);
}

bool HoneyPot::rmDir(std::string dirName) {
    return dirList.eraseDir(dirName);
}

std::set<std::string> HoneyPot::getDirList() {
    return dirList.get();
}
