#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H

#include "socket.h"

typedef struct {
    socket_t skt;
} client_t;

void client_init(client_t *self);

#endif //TP1_CLIENT_H
