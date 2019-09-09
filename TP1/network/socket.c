#include "socket.h"
#include <stdio.h>
#include <stdbool.h>
#include "debug.h"
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

bool socket_init(socket_t *self, int _fd) {
    if (_fd) {
        self->fd = _fd;
        return true;
    }
    int fd = socket(FAMILY, SOCK_TYPE, 0);
    if (fd == -1) {
        fprintf(stderr, "socket_init-->socket: %s\n", strerror(errno));
        return false;
    }
    self->fd = fd;
    return true;
}

struct addrinfo *_socket_get_addr(socket_t *self,
                                  const char *host, const char *service, int flags) {
    struct addrinfo *addr_list;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = FAMILY;
    hints.ai_socktype = SOCK_TYPE;
    hints.ai_flags = flags;
    int addr_err = 0;
    if ((addr_err = getaddrinfo(host, service, &hints, &addr_list)) != 0) {
        fprintf(stderr, "_socket_get_addr-->getaddrinfo: %s\n",
                gai_strerror(addr_err));
        socket_release(self);
        return false;
    }
    return addr_list;
}

bool socket_connect(socket_t *self, const char *host, const char *service) {
    bool connection_err = false;
    struct addrinfo *addr_list = _socket_get_addr(self, host,
                                                  service, CLIENT_FLAGS);

    struct addrinfo *addr = addr_list;
    for (; addr && !connection_err; addr = addr->ai_next) {
        if (connect(self->fd, addr->ai_addr, addr->ai_addrlen) == -1)
            connection_err = true;
    }

    freeaddrinfo(addr_list);

    if (connection_err) {
        fprintf(stderr, "socket_connect-->connect: %s\n",
                strerror(errno));
        socket_release(self);
        return false;
    }

    return true;
}

bool socket_bind(socket_t *self, const char *service) {
    bool bind_err = false;
    struct addrinfo *addr_list = _socket_get_addr(self, NULL,
                                                  service, SERVER_FLAGS);

    struct addrinfo *addr = addr_list;
    for (; addr && !bind_err; addr = addr->ai_next) {
        if (bind(self->fd, addr->ai_addr, addr->ai_addrlen) == -1)
            bind_err = true;
    }

    freeaddrinfo(addr_list);

    if (bind_err) {
        fprintf(stderr, "socket_bind-->bind: %s\n", strerror(errno));
        socket_release(self);
        return false;
    }

    return true;
}

int socket_listen(socket_t *self) {
    int s = listen(self->fd, 20);
    if (s == -1) {
        fprintf(stderr, "socket_listen-->listen: %s\n", strerror(errno));
        socket_release(self);
        return 1;
    }
    return 0;
}

int socket_accept(socket_t *self) {
    int fd = accept(self->fd, NULL, NULL);
    DEBUG_PRINT("New Client!\n");
    return fd;
}

ssize_t socket_send(socket_t *self, const char *request, size_t length) {
    int remaining_bytes = length;
    int total_bytes_sent = 0;
    ssize_t bytes = 0;
    while (total_bytes_sent < length) {
        bytes = send(self->fd, &request[total_bytes_sent],
                     remaining_bytes, MSG_NOSIGNAL);
        if (bytes == -1) {
            total_bytes_sent = -1;
            fprintf(stderr, "socket_send-->send: %s\n", strerror(errno));
            break;
        }
        if (bytes == 0) {
            total_bytes_sent = 0;
            break;
        }
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_sent;
}

ssize_t socket_receive(socket_t *self, char *response, size_t length) {
    int remaining_bytes = length;
    int total_bytes_received = 0;
    ssize_t bytes = 0;
    while (total_bytes_received < length) {
        bytes = recv(self->fd, &response[total_bytes_received],
                     remaining_bytes, 0);
        if (bytes == -1) {
            total_bytes_received = -1;
            fprintf(stderr, "socket_receive-->recv: %s\n", strerror(errno));
            break;
        }
        if (bytes == 0) {
            total_bytes_received = 0;
            break;
        }
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }
    return total_bytes_received;
}

void socket_release(socket_t *self) {
    if (!self) return;
    int err;
    err = shutdown(self->fd, SHUT_RDWR);
    if (err == -1) {
        fprintf(stderr, "socket_release-->shutdown: %s\n", strerror(errno));
    }
    err = close(self->fd);
    if (err == -1) {
        fprintf(stderr, "socket_release-->close: %s\n", strerror(errno));
    }
}
