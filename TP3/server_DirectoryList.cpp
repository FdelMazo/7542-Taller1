#include "server_DirectoryList.h"

bool DirectoryList::addDir(std::string &dirName) {
    std::unique_lock<std::mutex> lock(m);
    if (dirlist.count(dirName))
        return false;
    dirlist.insert(dirName);
    return true;
}

bool DirectoryList::eraseDir(std::string &dirName) {
    std::unique_lock<std::mutex> lock(m);
    if (!dirlist.count(dirName))
        return false;
    dirlist.erase(dirName);
    return true;
}

std::set<std::string> DirectoryList::get() {
    return dirlist;
}
