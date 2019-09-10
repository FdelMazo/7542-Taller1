#include "protocol.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "sudoku_dispatcher.h"

bool protocol_client_init(protocol_t *self, char *host, char *port) {
    bool no_err = true;
    socket_t *socket = malloc(sizeof(socket_t));
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
    if (!socket_bind(socket, port)) return false;
    socket_listen(socket);
    self->skt = socket;
    self->client_skt = NULL;
    return true;
}

//static ssize_t _encode_response(char *buf, char *message) {
//    *message = *buf;
//    return strlen(message);
//}
//
//static ssize_t _decode_response(char *buf, char *response) {
//    *response = *buf;
//    return strlen(response);
//}

// return -1 if the input is invalid
// returns 0 if the input is valid, but there is nothing else to send
// return n bytes if there are arguments to send
static ssize_t _encode_arguments(char *buf, char *message, uint8_t *arguments) {
    if (message[0] != 'P') return 0;
    char discard = 0;
    int arg1, arg2, arg3;
    sscanf(buf, "%s %d in %d,%d", &discard, &arg1, &arg2, &arg3);
    if (!sudoku_dispatcher_input_valid(arg1, arg2, arg3)) return -1;
    arguments[0] = '0' + arg1;
    arguments[1] = '0' + arg2;
    arguments[2] = '0' + arg3;
    return ARGUMENTS_LENGTH;
}


static ssize_t _encode_request(char *buf, char *message) {
    char action[MAX_LENGTH_COMMAND] = {0};
    ssize_t bytes = 0;
    sscanf(buf, "%s", action);
    if (strncmp(action, EXIT, strlen(EXIT)) == 0) {
        return -1;
    } else if (strncmp(action, PUT, strlen(PUT)) == 0) {
        message[bytes++] = 'P';
    } else if (strncmp(action, VERIFY, strlen(VERIFY)) == 0) {
        message[bytes++] = 'V';
    } else if (strncmp(action, RESET, strlen(RESET)) == 0) {
        message[bytes++] = 'R';
    } else if (strncmp(action, GET, strlen(RESET)) == 0) {
        message[bytes++] = 'G';
    }
    return bytes;
}

// Returns the n bytes the server must ask again
// (e.g. if the command is a get, nothing else is expected
//     if the command is a put, the server needs the arguments)
static bool _decode_request(char *request) {
    if (request[0] != 'P') return 0;
    return ARGUMENTS_LENGTH;
}

ssize_t protocol_client_send(protocol_t *self, char *request) {
    char msg[REQUEST_LENGTH] = {0};
    uint8_t arguments[ARGUMENTS_LENGTH] = {0};
    ssize_t bytes, arg_bytes;
    if ((bytes = _encode_request(request, msg)) == -1)
        return bytes;
    if ((arg_bytes = _encode_arguments(request, msg, arguments)) == -1)
        return 0;
//    DEBUG_PRINT("protocol received from client: %s"
//                "\ttranscribed to: %s\n", request, msg);
//    DEBUG_PRINT("protocol also sends: %s\n", arguments);
    socket_send(self->skt, msg, bytes);
    bytes += socket_send(self->skt, arguments, arg_bytes);
    return bytes;
}

ssize_t protocol_client_receive(protocol_t *self, char *buffer) {
    return socket_receive(self->skt, buffer, MAX_RESPONSE_LENGTH);
//    char response[MAX_RESPONSE_LENGTH] = {0};
//    return _decode_response(buffer, response);
}

void protocol_server_accept(protocol_t *self) {
    int client_skt = socket_accept(self->skt);
    self->client_skt = malloc(sizeof(socket_t));
    socket_init(self->client_skt, client_skt);
}

ssize_t protocol_server_receive(protocol_t *self, char *request) {
    ssize_t recv = socket_receive(self->client_skt, request, REQUEST_LENGTH);
    if (_decode_request(request) == 0) return recv;
    request += recv;
    recv += socket_receive(self->client_skt, request, ARGUMENTS_LENGTH);
    return recv;
}

ssize_t protocol_server_send(protocol_t *self, char *buffer) {
//    char response[MAX_RESPONSE_LENGTH] = {0};
//    ssize_t bytes = _encode_response(buffer, response);
    return socket_send(self->client_skt, buffer, MAX_RESPONSE_LENGTH);
}

void protocol_release(protocol_t *self) {
    if (!self) return;
    socket_release(self->skt);
    free(self->skt);
    socket_release(self->client_skt);
    free(self->client_skt);
}

