#include <stdio.h>
#include <string.h>
#include "network/client.h"
#include "network/server.h"

int main(int argc, char *argv[]) {
    int r = 0;
    if (argc > 1) {
        if (strncmp(argv[1], "server", 6) == 0)
            r = server_main(argc, argv);
        else if (strncmp(argv[1], "client", 6) == 0)
            r = client_main(argc, argv);
    } else {
        fprintf(stderr, "Modo no soportado, el primer parámetro debe ser server o client\n");
        r = -1;
    }
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return r;
}
