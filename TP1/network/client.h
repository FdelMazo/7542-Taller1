#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H

#include "socket.h"
#include <stdbool.h>

#define MAX_LENGTH 50

typedef struct {
    socket_t skt;
} client_t;

bool client_init(client_t *self, char *host, char *port);
void client_communicate(client_t *self);
void client_release(client_t *self);

#endif //TP1_CLIENT_H
