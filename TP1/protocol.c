#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

bool protocol_client_init(protocol_t *self, char *host, char *port) {
    bool no_err = true;
    socket_t *socket = malloc(sizeof(socket_t));
    no_err &= socket_init(socket, 0);
    no_err &= socket_connect(socket, host, port);

    self->skt = socket;
    self->client_skt = calloc(1, sizeof(socket_t));

    if (!self->skt || !self->client_skt || !no_err) {
        free(self->skt);
        free(self->client_skt);
        return false;
    }
    return true;
}

bool protocol_server_init(protocol_t *self, char *port) {
    socket_t *socket = malloc(sizeof(socket_t));
    if (!socket_init(socket, 0)) return false;
    if (!socket_bind(socket, port)) return false;
    socket_listen(socket);
    self->skt = socket;
    self->client_skt = NULL;
    return true;
}

ssize_t _protocol_encode(char *buf, char *message) {
    char action[MAX_LENGTH_COMMAND];
    sscanf(buf, "%s", action);
    buf += strlen(action) + 1;
    if (strncmp(action, PUT, strlen(PUT)) == 0) {
        message[0] = 'P';
        sscanf(buf, "%c in %c,%c", &message[1], &message[2], &message[3]);
    } else if (strncmp(action, EXIT, strlen(EXIT)) == 0) {
        return 0;
    } else if (strncmp(action, VERIFY, strlen(VERIFY)) == 0) {
        message[0] = 'V';
    } else if (strncmp(action, RESET, strlen(RESET)) == 0) {
        message[0] = 'R';
    } else if (strncmp(action, GET, strlen(RESET)) == 0) {
        message[0] = 'G';
    }
    return MAX_REQUEST_LENGTH;
}

ssize_t protocol_client_send(protocol_t *self, char *buf) {
    char msg[MAX_REQUEST_LENGTH + 1];
    ssize_t bytes = _protocol_encode(buf, msg);
    DEBUG_PRINT("protocol received from client: %s"
                "\ttranscribed to: %s\n", buf, msg);
    return socket_send(self->skt, msg, bytes);
}

ssize_t protocol_client_receive(protocol_t *self, char *response) {
    int r = socket_receive(self->skt, response, MAX_RESPONSE_LENGTH);
    return r;
}

ssize_t protocol_server_send(protocol_t *self, char *buf) {
    char *ptr = buf;
    return socket_send(self->client_skt, ptr, MAX_RESPONSE_LENGTH);
}

ssize_t protocol_server_receive(protocol_t *self, char *buf) {
    if (!self->client_skt) {
        int client_skt = socket_accept(self->skt);
        self->client_skt = malloc(sizeof(socket_t));
        socket_init(self->client_skt, client_skt);
    }
    return socket_receive(self->client_skt, buf, MAX_REQUEST_LENGTH);
}

void protocol_release(protocol_t *self) {
    if (!self) return;
    socket_release(self->skt);
    free(self->skt);
    socket_release(self->client_skt);
    free(self->client_skt);
}
