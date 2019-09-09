#include <stdio.h>
#include <string.h>
#include "network/client.h"
#include "network/server.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (strncmp(argv[1], "server", 6) == 0)
            return server_main(argc, argv);
        else if (strncmp(argv[1], "client", 6) == 0)
            return client_main(argc, argv);
    }
    fprintf(stderr, "Modo no soportado, el primer parámetro debe ser server o client\n");
    return 1;
}
