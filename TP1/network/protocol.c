#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "sudoku_dispatcher.h"

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
    char action[MAX_LENGTH_COMMAND] = {0};
    sscanf(buf, "%s", action);
    buf += strlen(action) + 1;
    if (strncmp(action, PUT, strlen(PUT)) == 0) {
        message[0] = 'P';
        int arg1, arg2, arg3;
        sscanf(buf, "%d in %d,%d", &arg1, &arg2, &arg3);
        if (!sudoku_dispatcher_input_valid(arg1, arg2, arg3)) return 0;
        message[1] = '0' + arg1;
        message[2] = '0' + arg2;
        message[3] = '0' + arg3;
    } else if (strncmp(action, EXIT, strlen(EXIT)) == 0) {
        return -1;
    } else if (strncmp(action, VERIFY, strlen(VERIFY)) == 0) {
        message[0] = 'V';
    } else if (strncmp(action, RESET, strlen(RESET)) == 0) {
        message[0] = 'R';
    } else if (strncmp(action, GET, strlen(RESET)) == 0) {
        message[0] = 'G';
    } else {
        return 0;
    }
    return MAX_REQUEST_LENGTH;
}

ssize_t protocol_client_send(protocol_t *self, char *request) {
    char msg[MAX_REQUEST_LENGTH + 1] = {0};
    ssize_t bytes = _protocol_encode(request, msg);
    if (bytes == -1) return -1;
//    DEBUG_PRINT("protocol received from client: %s"
//                "\ttranscribed to: %s\n", request, msg);
    return socket_send(self->skt, msg, bytes);
}

ssize_t protocol_client_receive(protocol_t *self, char *response) {
    return socket_receive(self->skt, response, MAX_RESPONSE_LENGTH);
}

ssize_t protocol_server_receive(protocol_t *self, char *request) {
    if (!self->client_skt) {
        int client_skt = socket_accept(self->skt);
        self->client_skt = malloc(sizeof(socket_t));
        socket_init(self->client_skt, client_skt);
    }
    return socket_receive(self->client_skt, request, MAX_REQUEST_LENGTH);
}

ssize_t protocol_server_send(protocol_t *self, char *response) {
    return socket_send(self->client_skt, response, MAX_RESPONSE_LENGTH);
}

void protocol_release(protocol_t *self) {
    if (!self) return;
    socket_release(self->skt);
    free(self->skt);
    socket_release(self->client_skt);
    free(self->client_skt);
}

