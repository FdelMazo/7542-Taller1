#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "socket.h"

typedef struct {
    socket_t skt;
    socket_t client_skt;
} server_t;

#define MAX_LENGTH 50

void server_init(server_t *self, char* port);
void server_communicate(server_t *self);
void server_release(server_t *self);

#endif //TP1_SERVER_H
