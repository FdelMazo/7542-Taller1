#include <stdio.h>
#include <string.h>
#include "network/client.h"
#include "network/server.h"

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strncmp(argv[1], "server", 6) == 0) {
            if (argc != 3) {
                fprintf(stderr, "Uso: ./tp server <puerto>\n");
                return 1;
            }
            server_t server;
            server_init(&server, argv[2]);
        }
        else if (strncmp(argv[1], "client", 6) == 0) {
            if (argc != 4) {
                fprintf(stderr, "Uso: ./tp server <puerto>\n");
                return 1;
            }
            client_t client;
            client_init(&client);
        }
    }
    else {
        fprintf(stderr, "Modo no soportado, el primer parámetro debe ser server o client\n");
        return 1;
    }

	return 0;
}