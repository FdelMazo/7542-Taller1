#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H

#include "protocol.h"
#include <stdbool.h>


typedef struct {
    protocol_t *protocol;
} client_t;

int client_main(int argc, char *argv[]);

bool client_init(client_t *self, char *host, char *port);

void client_communicate(client_t *self);

void client_release(client_t *self);

#endif //TP1_CLIENT_H
