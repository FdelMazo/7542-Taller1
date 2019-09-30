#include "server_HoneyPot.h"
#include "server_Server.h"

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    char *port = argv[1];
    char *configFileName = argv[2];
    Server server(port, configFileName);
    while (true) {
        std::string request = server.receiveRequest();
        std::string response = server.processRequest(request);
        server.sendResponse(response);
    }
    return 0;
}
