#include <sstream>
#include "server_CommandListDirs.h"

std::string CommandListDirs::run(std::string &dummyArg, bool *alive) {
    std::unique_lock<std::mutex> lock(m);
    if (!pot->validCredentials(this->username, this->password))
        return notLoggedResponse();
    std::ostringstream stream;
    stream << response(150, pot->getAnswer("listBegin"));
    for (const std::string &dir : pot->getDirList()) {
        stream << "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34";
        stream << " " << dir << "" << '\n';
    }
    stream << response(226, pot->getAnswer("listEnd"));
    return stream.str();
}
