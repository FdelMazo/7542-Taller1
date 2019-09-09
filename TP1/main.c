#include <stdio.h>
#include <string.h>
#include "network/client.h"
#include "network/server.h"

#define SERVER "server"
#define CLIENT "client"
#define ERR "Modo no soportado, el primer parámetro debe ser server o client\n"

int main(int argc, char *argv[]) {
    int r = 0;
    if (argv[1] && strncmp(argv[1], SERVER, strlen(SERVER)) == 0)
        r = server_main(argc, argv);
    else if (strncmp(argv[1], CLIENT, strlen(CLIENT)) == 0)
        r = client_main(argc, argv);
    else {
        fprintf(stderr, ERR);
        r = -1;
    }
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return r;
}
