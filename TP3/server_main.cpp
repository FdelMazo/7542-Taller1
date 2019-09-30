#include <iostream>
#include <sstream>
#include <vector>
#include "server_HoneyPot.h"
#include "server_ClientProxy.h"

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    char *port = argv[1];
    char *configFileName = argv[2];
    HoneyPot pot(configFileName);
    ClientProxy client(port);
    while (true) {
        std::string request = client.communicate();
        std::istringstream stream(request);
        std::vector<std::string> command;
        std::string buff;
        while ( getline(stream, buff, ' ' ) ) {
            command.emplace_back(buff);
        }
        std::string response = pot.runCommand(command[0], command[1]);
        client.communicate(response);
    }
    return 0;
}
