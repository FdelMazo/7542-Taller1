#ifndef TP1_SERVER_HONEYPOT_H
#define TP1_SERVER_HONEYPOT_H


#include <set>
#include <string>
#include <map>

class HoneyPot {
    std::set<std::string> dirList = {};
    std::map<std::string, std::string> config;

public:
    static const int UNKNOWN_COMMAND_RC = 500;
    const std::string UNKNOWN_COMMAND_MSG = "unknownCommand";
    static const int NEW_CLIENT_RC = 230;
    const std::string NEW_CLIENT_MSG = "newClient";
    static const int QUIT_RC = 221;
    const std::string QUIT_MSG = "quitSuccess";

    bool logged(std::string *username, std::string *password);

    explicit HoneyPot(std::string configFileName);

    std::string
    runCommand(std::string commandName, std::string arg, std::string *user, std::string *pass, bool *pBoolean);

    std::string getMsg(std::string key);

    std::set<std::string> getDirList();

    bool makeDir(std::string basicString);

    bool rmDir(std::string dirName);

    std::string acceptClient();

};


#endif //TP1_SERVER_HONEYPOT_H
