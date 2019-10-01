#ifndef TP3_COMMON_SOCKET_H
#define TP3_COMMON_SOCKET_H

#include <string>
#include <sys/types.h>

class Socket {
//    static static const int FAMILY = AF_INET;
//    static static const int SOCK_TYPE = SOCK_STREAM;
//    static static const int CLIENT_FLAGS = 0;
//    static static const int SERVER_FLAGS = AI_PASSIVE;

public:
    Socket();

    Socket(int i);

    void connect(char *host, char *port);

    void send(const void *msg, size_t length);

    void recv(void *response, size_t length);

    void bind(char *port);

    Socket accept();

    void listen();

    int fd;

    void close();

private:
    struct addrinfo *_get_addr(const char *host, const char *service, int flags);

};

#endif //TP3_COMMON_SOCKET_H
