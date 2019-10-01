#ifndef TP3_SERVER_DIRECTORYLIST_H
#define TP3_SERVER_DIRECTORYLIST_H


#include <string>
#include <set>
#include <mutex>

class DirectoryList {
    std::set<std::string> dirlist = {};
    std::mutex m;
public:
    bool rmDir(std::string basicString);

    std::set<std::string> get();

    bool mkDir(std::string dirName);
};


#endif //TP3_SERVER_DIRECTORYLIST_H
