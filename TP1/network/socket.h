#ifndef TP1_SOCKET_H
#define TP1_SOCKET_H

#include <stdlib.h>
#include <stdbool.h>

#define FAMILY AF_INET
#define SOCK_TYPE SOCK_STREAM
#define CLIENT_FLAGS 0
#define SERVER_FLAGS AI_PASSIVE

typedef struct {
	int fd;
} socket_t;

bool socket_init(socket_t* self, int _fd);

void socket_release(socket_t* self);

bool socket_connect(socket_t* self, const char* host, const char* service);

ssize_t socket_send(socket_t* self, const char* message, size_t length);

ssize_t socket_receive(socket_t* self, char* response, size_t length);

bool socket_bind(socket_t* self, const char* service);

int socket_listen(socket_t* socket);

int socket_accept(socket_t *self);


#endif //TP1_SOCKET_H
