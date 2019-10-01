#include <sstream>
#include <algorithm>
#include "server_CommandListDirs.h"

std::string CommandListDirs::run(std::string dummyArg, std::string *username, std::string *password) {
    if (!pot->logged(username, password)) return notLoggedResponse();
    std::ostringstream stream;
    stream << response(BEGIN_RC, pot->getMsg(BEGIN_MSG));
    for (const std::string dir : pot->getDirList()) {
        stream << DUMMY_LS << " \"" << dir << "\"" << '\n';
    }
    stream << response(END_RC, pot->getMsg(END_MSG));
    return stream.str();
}
