#include "server.h"
#include <stdio.h>

void server_init(server_t *self, char* port_number) {
    socket_t socket;
    socket_init(&socket);
    socket_bind(&socket, "127.0.0.1", port_number);
    socket_listen(&socket);
    self->skt = socket;
}