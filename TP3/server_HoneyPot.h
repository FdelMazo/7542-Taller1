#ifndef TP1_SERVER_HONEYPOT_H
#define TP1_SERVER_HONEYPOT_H


#include <set>
#include <string>
#include <map>
#include "server_DirectoryList.h"

class HoneyPot {
public:
    explicit HoneyPot(std::string &configFileName);

    bool validCredentials(std::string &username, std::string &password);

    std::string & getAnswer(const std::string &command);

    bool mkDir(std::string &dirName);

    bool rmDir(std::string &dirName);

    std::set<std::string> getDirList();

private:
    DirectoryList dirList;
    std::map<std::string, std::string> config;
};


#endif //TP1_SERVER_HONEYPOT_H
