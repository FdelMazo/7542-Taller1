#ifndef TP3_SERVER_DIRECTORYLIST_H
#define TP3_SERVER_DIRECTORYLIST_H


#include <string>
#include <set>
#include <mutex>

class DirectoryList {
public:
    bool addDir(std::string dirName);

    bool eraseDir(std::string dirName);

    std::set<std::string> get();

private:
    std::set<std::string> dirlist = {};
    std::mutex m;
};


#endif //TP3_SERVER_DIRECTORYLIST_H
