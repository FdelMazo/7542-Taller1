#include <iostream>
#include "client_ServerProxy.h"

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    char *host = argv[1];
    char *port = argv[2];
    ServerProxy server(host, port);
    while (true) {
        std::string request;
        getline(std::cin, request);
        request+='\n';
        std::string response = server.communicate(request);
        std::cout << response;
    }
    return 0;
}
