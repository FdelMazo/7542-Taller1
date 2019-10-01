#include <cstring>
#include <unistd.h>
#include <stdexcept>
#include "common_Socket.h"

Socket::Socket(int i) {
    this->fd = i;
}

void Socket::connect(char *host, char *port) {
    bool connection_err = false;
    struct addrinfo *addr_list;
    addr_list = getAddr(host, port, CLIENT_FLAGS);
    int filedesc = -1;
    struct addrinfo *addr = addr_list;
    for (; addr && !connection_err; addr = addr->ai_next) {
        filedesc = socket(addr->ai_family, addr->ai_socktype,
                          addr->ai_protocol);
        if (::connect(filedesc, addr->ai_addr, addr->ai_addrlen) == -1)
            connection_err = true;
    }
    this->fd = filedesc;
    freeaddrinfo(addr_list);
}

void Socket::bind(char *port) {
    bool bind_err = false;
    struct addrinfo *addr_list;
    addr_list = getAddr(nullptr, port, SERVER_FLAGS);
    int filedesc = -1;
    struct addrinfo *addr = addr_list;
    for (; addr && !bind_err; addr = addr->ai_next) {
        filedesc = socket(addr->ai_family, addr->ai_socktype,
                          addr->ai_protocol);
        if (::bind(filedesc, addr->ai_addr, addr->ai_addrlen) == -1)
            bind_err = true;
    }
    this->fd = filedesc;
    freeaddrinfo(addr_list);
}

void Socket::listen() {
    ::listen(this->fd, 20);
}

Socket Socket::accept() {
    int filedesc = ::accept(this->fd, nullptr, nullptr);
    if (filedesc == -1)
        throw std::invalid_argument("socket closed");
    return Socket(filedesc);
}

void Socket::close() {
    ::shutdown(this->fd, SHUT_RDWR);
    ::close(this->fd);
}

void Socket::send(const void *msg, size_t length) {
    if (length == 0) return;
    int remaining_bytes = length;
    uint total_bytes_sent = 0;
    ssize_t bytes = 0;
    const char *send_request = static_cast<const char *>(msg);
    while (total_bytes_sent < length) {
        bytes = ::send(this->fd, &send_request[total_bytes_sent],
                       remaining_bytes, MSG_NOSIGNAL);
        if (bytes <= 0)
            break;
        total_bytes_sent += bytes;
        remaining_bytes -= bytes;
    }
}

void Socket::recv(void *response, size_t length) {
    if (length == 0) return;
    int remaining_bytes = length;
    uint total_bytes_received = 0;
    ssize_t bytes = 0;
    char *recv_response = static_cast<char *>(response);
    while (total_bytes_received < length) {
        bytes = ::recv(this->fd, &recv_response[total_bytes_received],
                       remaining_bytes, 0);
        if (bytes <= 0)
            break;
        total_bytes_received += bytes;
        remaining_bytes -= bytes;
    }
}

struct addrinfo *Socket::getAddr(const char *host, const char *service,
                                 int flags) {
    struct addrinfo *addr_list;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = FAMILY;
    hints.ai_socktype = SOCK_TYPE;
    hints.ai_flags = flags;
    int addr_err = 0;
    if ((addr_err = getaddrinfo(host, service, &hints, &addr_list)) != 0)
        return nullptr;
    return addr_list;
}
