#include "socket.h"
#include <stdio.h> // printf()
#include <stdbool.h> // bool
#include <string.h> // memset()
#include <netdb.h> // getaddrinfo()
#include <sys/socket.h> // socket()
#include <errno.h> // errno
#include <unistd.h> // close()

void socket_init(socket_t *self) {
	int fd = socket(AF_INET, SOCK_STREAM, 6);
	if (fd == -1) {
		fprintf(stderr, "socket_init-->socket: %s\n", strerror(errno));
		return;
	}
	self->fd = fd;
}

void socket_release(socket_t *self){
	shutdown(self->fd, SHUT_RDWR);
	int err = close(self->fd);
	if (err == -1) {
		fprintf(stderr, "socket_release-->close: %s\n", strerror(errno));
	}
}

int socket_connect(socket_t *self, const char *host, const char *service) {
	int addr_err, connection_err;
	struct addrinfo hints;
	struct addrinfo *addr_list;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = 0;
	if ( (addr_err = getaddrinfo(host, service, &hints, &addr_list)) != 0) {
		fprintf(stderr, "socket_connect-->getaddrinfo: %s\n", gai_strerror(addr_err));
		return addr_err;
	}

	for (struct addrinfo *addr = addr_list; addr != NULL && connection_err != 0; addr = addr->ai_next) {
		connection_err = connect(self->fd, addr->ai_addr, addr->ai_addrlen);
	}

	if (connection_err == -1) {
		fprintf(stderr, "socket_connect-->connect: %s\n", strerror(errno));
		socket_release(self);
		return errno;
	}

	freeaddrinfo(addr_list);
	return 1;
}

int socket_send(socket_t* self, const char* buffer, size_t length) {
	bool err = false;
	int remaining_bytes = length;
	int bytes_sent = 0;
	int bytes;
	while (bytes_sent < length && !err) {
		bytes = send(self->fd, &buffer[bytes_sent], remaining_bytes, MSG_NOSIGNAL);
		if (bytes <= 0){
			err = true;
			fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
		} else {
			bytes_sent += bytes;
			remaining_bytes -= bytes;
		}
	}
	return bytes;
}

int socket_receive(socket_t* self, char* response, size_t length) {
    bool err = false;
    int remaining_bytes = length;
    int bytes_received = 0;
    int bytes;
    while (bytes_received < length && !err) {
        bytes = recv(self->fd, &response[bytes_received], remaining_bytes, 0);
        if (bytes <= 0) {
            err = true;
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
        } else {
            bytes_received += bytes;
            remaining_bytes -= bytes;
        }
    }
    return bytes;
}

int socket_bind(socket_t* self, const char* host, const char* service) {
    int addr_err, bind_err;
    struct addrinfo hints;
    struct addrinfo *addr_list;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    if ( (addr_err = getaddrinfo(host, service, &hints, &addr_list)) != 0) {
        fprintf(stderr, "socket_bind-->getaddrinfo: %s\n", gai_strerror(addr_err));
        return addr_err;
    }

    bind_err = bind(self->fd, addr_list->ai_addr, addr_list->ai_addrlen);
//    for (struct addrinfo *addr = addr_list; addr != NULL && bind_err != 0; addr = addr->ai_next) {
//        bind_err = bind(self->fd, addr->ai_addr, addr->ai_addrlen);
//    }

    if (bind_err == -1) {
        fprintf(stderr, "socket_bind-->bind: %s\n", strerror(errno));
        socket_release(self);
        return errno;
    }

    freeaddrinfo(addr_list);
}

int socket_listen(socket_t* self) {
    int s = listen(self->fd, 20);
    if (s == -1) {
        fprintf(stderr, "socket_listen-->listen: %s\n", strerror(errno));
        socket_release(self);
        return 1;
    }
    while (true) {
        accept(self->fd, NULL, NULL);
        printf("New client\n");
    }
    return 1;
}