#include "client.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "protocol.h"

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

void client_release(client_t *self){
    protocol_release(self->protocol);
}

bool client_init(client_t *self, char* host, char *port) {
    protocol_t protocol;
    protocol_client_init(&protocol, host, port);
    self->protocol = &protocol;
    return true;
}

bool _client_exit(char *command){
    if (strncmp(command, EXIT_COMMAND, strlen(EXIT_COMMAND)) == 0) return true;
    return false;
}

void client_communicate(client_t *self) {
    char *command = calloc(MAX_LENGTH_COMMAND, sizeof(char));
    char* output = calloc(MAX_LENGTH_OUTPUT, sizeof(char));
    while (true) {
        command = fgets(command, MAX_LENGTH_COMMAND, stdin);
        if (_client_exit(command)) {
            break;
        }
        DEBUG_PRINT("client sending: %s\n", command);
        protocol_client_send(self->protocol, command);
        protocol_client_receive(self->protocol, output);
        DEBUG_PRINT("client got back: %s\n", output);
        printf("%s", output);
    }
    free(command);
    free(output);
}
