#include "server.h"
#include <stdio.h>
#include <string.h>

void server_init(server_t *self, char* port_number) {
    socket_t socket;
    socket_init(&socket, 0);
    socket_bind(&socket, port_number);
    socket_listen(&socket);
    self->skt = socket;
}

bool server_send(server_t* self, char *buf) {
    if (socket_send(&self->client_skt, buf, 3) == -1) return false;
    return true;
}

bool server_receive(server_t *self, char *buf) {
    if (socket_receive(&self->client_skt, buf, 3) == -1) return false;
    return true;
}

void server_communicate(server_t *self){
    while (true) {
        int client_skt = socket_accept(&self->skt);
        socket_t socket;
        socket_init(&socket, client_skt);
        self->client_skt = socket;
        while (true) {
            char* client_request = calloc(MAX_LENGTH, 1);
            server_receive(self, client_request);
            printf("Yo, server, recibi: %s\n", client_request);
            char* server_response = calloc(MAX_LENGTH, 1);
            server_response = "fed";
            printf("Yo, server, contesto: %s\n", server_response);
            server_send(self, server_response);
        }
    }
}

void server_release(server_t *self) {
    socket_release(&self->skt);
}
