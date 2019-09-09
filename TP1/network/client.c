#include "client.h"
#include "debug.h"
#include <stdio.h>
#include <unistd.h>
#include "protocol.h"
#include <stdbool.h>

int client_main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: ./tp client <host> <puerto>\n");
        return 1;
    }
    client_t client;
    if (!client_init(&client, argv[2], argv[3])) return 1;
    client_communicate(&client);
    client_release(&client);
    return 0;
}

bool client_init(client_t *self, char *host, char *port) {
    protocol_t *protocol = malloc(sizeof(protocol_t));
    if (!protocol || !protocol_client_init(protocol, host, port)) {
        free(protocol);
        return false;
    }
    self->protocol = protocol;
    return true;
}

void client_communicate(client_t *self) {
    while (true) {
        char command[MAX_LENGTH_COMMAND] = {0};
        if (!fgets(command, MAX_LENGTH_COMMAND, stdin)) break;
//        DEBUG_PRINT("client sending: %s\n", command);
        ssize_t send = protocol_client_send(self->protocol, command);
        if (send == -1) break;
        else if (send == 0) continue;
        char output[MAX_LENGTH_OUTPUT] = {0};
        ssize_t received = protocol_client_receive(self->protocol, output);
        if (received <= 0) break;
        printf("%s", output);
    }
}

void client_release(client_t *self) {
    if (!self) return;
    protocol_release(self->protocol);
    free(self->protocol);
}
