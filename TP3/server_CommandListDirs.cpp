#include <sstream>
#include "server_CommandListDirs.h"

std::string CommandListDirs::run(std::string dummyArg, std::string *username, std::string *password, bool *pBoolean) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    std::ostringstream stream;
//    stream << response(BEGIN_RC, pot->getMsg(BEGIN_MSG));
    stream << response(150, pot->getMsg("listBegin"));
    for (const std::string dir : pot->getDirList()) {
//        stream << DUMMY_LS << " \"" << dir << "\"" << '\n';
        stream << "drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34" << " " << dir << "" << '\n';
    }
//    stream << response(END_RC, pot->getMsg(END_MSG));
    stream << response(226, pot->getMsg("listEnd"));
    return stream.str();
}
