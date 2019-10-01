#include <iostream>
#include "client_Client.h"

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    char *host = argv[1];
    char *port = argv[2];
    Client client(host, port);
    while (true) {
        std::string request;
        getline(std::cin, request);
        client.sendRequest(request);
        std::string response = client.getResponse();
        std::cout << response;
    }
    return 0;
}
