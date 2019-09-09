#ifndef TP1_PROTOCOL_H
#define TP1_PROTOCOL_H

#define MAX_LENGTH_COMMAND 15
#define MAX_LENGTH_OUTPUT 800
#define MAX_REQUEST_LENGTH 4
#define MAX_RESPONSE_LENGTH 800

#define PUT "put"
#define GET "get"
#define VERIFY "verify"
#define RESET "reset"
#define EXIT "exit"

#include "socket.h"
#include <sys/types.h>

typedef struct {
    socket_t *skt;
    socket_t *client_skt;
} protocol_t;

bool protocol_client_init(protocol_t *self, char *host, char *port);

bool protocol_server_init(protocol_t *self, char *port);

ssize_t protocol_client_send(protocol_t *self, char *buf);

ssize_t protocol_client_receive(protocol_t *self, char *response);

ssize_t protocol_server_send(protocol_t *self, char *buf);

ssize_t protocol_server_receive(protocol_t *self, char *buf);

void protocol_release(protocol_t *self);

#endif //TP1_PROTOCOL_H
