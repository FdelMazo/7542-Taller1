#ifndef TP1_SOCKET_H
#define TP1_SOCKET_H

#include <stdlib.h>

typedef struct {
	int fd;
} socket_t;


void socket_init(socket_t* self);

void socket_release(socket_t* self);

int socket_connect(socket_t* self, const char* host, const char* service);

int socket_send(socket_t* self, const char* message, size_t length);

int socket_receive(socket_t* self, char* response, size_t length);

int socket_bind(socket_t* self, const char* host, const char* service);

int socket_listen(socket_t* socket);

#endif //TP1_SOCKET_H
