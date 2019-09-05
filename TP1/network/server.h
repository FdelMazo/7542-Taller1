#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "socket.h"

typedef struct {
    socket_t skt;
} server_t;

void server_init(server_t *self, char* port_number);

#endif //TP1_SERVER_H
