#include "client.h"

void client_init(client_t *self) {
    socket_t socket;
    socket_init(&socket);
    socket_connect(&socket, "127.0.0.1", "5512");
    socket_send(&socket, "HELLO", 5);
    self->skt = socket;
}