#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include "common_Socket.h"

struct addrinfo *Socket::_get_addr(const char *host, const char *service, int flags) {
    struct addrinfo *addr_list;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flags;
    int addr_err = 0;
    if ((addr_err = getaddrinfo(host, service, &hints, &addr_list)) != 0) {
        return NULL;
    }
    return addr_list;
}

void Socket::sendMsg(const void *msg, size_t length) {
    if (length == 0) return;
    int remaining_bytes = length;
    uint total_bytes_sent = 0;
    ssize_t bytes = 0;
    const char *send_request = static_cast<const char *>(msg);
    while (total_bytes_sent < length) {
        bytes = send(this->fd, &send_request[total_bytes_sent],
                        remaining_bytes, MSG_NOSIGNAL);
        if (bytes == -1) {
            total_bytes_sent = -1;
            break;
        }
        if (bytes == 0)
            break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
}

void Socket::recvMsg(void *response, size_t length) {
    if (length == 0) return;
    int remaining_bytes = length;
    uint total_bytes_received = 0;
    ssize_t bytes = 0;
    char *recv_response = static_cast<char *>(response);
    while (total_bytes_received < length) {
        bytes = recv(this->fd, &recv_response[total_bytes_received],
                     remaining_bytes, 0);
        if (bytes == -1) {
            total_bytes_received = -1;
            break;
        }
        if (bytes == 0)
            break;
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }
}

void Socket::binding(char *port) {
    bool bind_err = false;
    struct addrinfo *addr_list;
    addr_list = _get_addr(NULL, port, AI_PASSIVE);
    int filedesc = -1;
    struct addrinfo *addr = addr_list;
    for (; addr && !bind_err; addr = addr->ai_next) {
        filedesc = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (bind(filedesc, addr->ai_addr, addr->ai_addrlen) == -1)
            bind_err = true;
    }
    this->fd = filedesc;
    freeaddrinfo(addr_list);
}

void Socket::connection(char *host, char *port) {
    bool connection_err = false;
    struct addrinfo *addr_list;
    addr_list = _get_addr(host, port, 0);
    int filedesc = -1;
    struct addrinfo *addr = addr_list;
    for (; addr && !connection_err; addr = addr->ai_next) {
        filedesc = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (connect(filedesc, addr->ai_addr, addr->ai_addrlen) == -1)
            connection_err = true;
    }
    this->fd = filedesc;

    freeaddrinfo(addr_list);
}

Socket Socket::acceptConnection() {
    int filedesc = accept(this->fd, NULL, NULL);
    return Socket(filedesc);
}

Socket::Socket(int i) {
    this->fd = i;
}

Socket::Socket() {

}

void Socket::listening() {
    listen(this->fd, 20);
}


