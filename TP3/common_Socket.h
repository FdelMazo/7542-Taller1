#ifndef TP3_COMMON_SOCKET_H
#define TP3_COMMON_SOCKET_H

#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>

class Socket {
    static const int FAMILY = AF_INET;
    static const int SOCK_TYPE = SOCK_STREAM;
    static const int CLIENT_FLAGS = 0;
    static const int SERVER_FLAGS = AI_PASSIVE;

public:
    Socket() = default;

    explicit Socket(int i);
    void connect(char *host, char *port);
    void bind(char *port);

    void listen();

    Socket accept();
    void close();

    void send(const void *msg, size_t length);

    void recv(void *response, size_t length);
private:
    int fd;
    struct addrinfo *_get_addr(const char *host, const char *service, int flags);
};

#endif //TP3_COMMON_SOCKET_H
