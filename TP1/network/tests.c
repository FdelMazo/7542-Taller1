#include <stdio.h>
#include <string.h>
#include "network/client.h"
#include "network/server.h"

int main(int argc, char* argv[]) {
    if (strncmp(argv[1], "server", 6) == 0) {
        server_t server;
        server_init(&server, argv[2]);
        server_communicate(&server);
        server_release(&server);
    }
    else if (strncmp(argv[1], "client", 6) == 0) {
        client_t client;
        client_init(&client, argv[2], argv[3]);
        client_communicate(&client);
        client_release(&client);
    }
}
