#include "client.h"
#include <string.h>
#include <stdio.h>
#include "protocol.h"

bool client_send(client_t* self, char *buf) {
    if (socket_send(&self->skt, buf, 3) == -1) return false;
    return true;
}

bool client_receive(client_t* self, char* buf) {
    if (socket_receive(&self->skt, buf, 3) == -1) return false;
    return true;
}

void client_release(client_t *self){
    socket_release(&self->skt);
}

bool client_init(client_t *self, char* host, char *port) {
    socket_t socket;
    if (!socket_init(&socket, 0)) return false;
    if (!socket_connect(&socket, host, port)) return false;
    self->skt = socket;
    return true;
}

bool client_command(client_t *self, char *buf) {
    printf("Yo, cliente, mando: %s\n", buf);
    client_send(self, buf);
    char* response = calloc(MAX_LENGTH, 1);
    client_receive(self, response);
    printf("Yo, cliente, recibo: %s\n", response);
    return true;
}

void client_communicate(client_t *self) {
    char *command = calloc(MAX_LENGTH, sizeof(char));
    command = fgets(command, MAX_LENGTH, stdin);
    while (client_command(self, command)) {
        command = fgets(command, MAX_LENGTH, stdin);
    }
}
