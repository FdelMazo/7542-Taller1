#ifndef TP1_PROTOCOL_H
#define TP1_PROTOCOL_H

#define MAX_ARGUMENTS 4
#define MAX_REQUEST_LENGTH 4
#define MAX_RESPONSE_LENGTH 800

#define PUT "put"
#define GET "get"
#define VERIFY "verify"
#define RESET "reset"

#include "socket.h"

typedef struct {
    socket_t *skt;
    socket_t *client_skt;
} protocol_t;

void protocol_release(protocol_t *self);
bool protocol_server_init(protocol_t *self, char *port);
bool protocol_client_init(protocol_t *self, char *host, char *port);

ssize_t protocol_client_send(protocol_t *self, char *buf);
ssize_t protocol_client_receive(protocol_t *self, char* response);
ssize_t protocol_server_send(protocol_t *self, char *buf);
ssize_t protocol_server_receive(protocol_t *self, char *buf);

#endif //TP1_PROTOCOL_H