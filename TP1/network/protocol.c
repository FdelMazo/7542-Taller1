#include "protocol.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

void _protocol_encode_command(char* message, int argc, char** argv){
    char *args = message;
    if (strncmp(argv[0], PUT, strlen(PUT)) == 0) {
        args[0] = 'P';
        args[1] = *argv[1];
        args[2] = argv[3][0];
        args[3] = argv[3][2];
    }
    else if (strncmp(argv[0], VERIFY, strlen(VERIFY)) == 0) {
        args[0] = 'V';
    }
    else if (strncmp(argv[0], RESET, strlen(RESET)) == 0) {
        args[0] = 'R';
    }
    else if (strncmp(argv[0], GET, strlen(RESET)) == 0) {
        args[0] = 'G';
    }
}

void _protocol_encode(char *buf, char* message) {
    char *ptr = buf;
    int argc = 0;
    char **argv = calloc(MAX_ARGUMENTS, sizeof(char*));
    for (int i=0; i< MAX_ARGUMENTS; i++) {
        char *argg = calloc(50, sizeof(char));
        sscanf(ptr, "%s", argg);
        ptr += strlen(argg) +1;
        argc++;
        argv[i] = argg;
    }
    for (int i=argc; i< MAX_ARGUMENTS; i++) {
        free(argv[i]);
    }
    _protocol_encode_command(message, argc, argv);
}

ssize_t protocol_client_send(protocol_t *self, char *buf){
    char msg[MAX_REQUEST_LENGTH+1];
    _protocol_encode(buf, msg);
    DEBUG_PRINT("protocol received from client: %s"
                "\ttranscribed to: %s\n", buf, msg);
    return socket_send(self->skt, msg, MAX_REQUEST_LENGTH) == -1;
}

ssize_t protocol_client_receive(protocol_t *self, char* response){
    char len_buf[1];
    if (socket_receive(self->skt, len_buf, 1 == -1)) return -1;
    int len = atoi(len_buf);
    char buf[len];
    int r = socket_receive(self->skt, response, 800);
    if (r > 0) {
        DEBUG_PRINT("protocol received a %d string from server: %s", len, buf);
        *response = *buf;
    }
    return r;
}

ssize_t protocol_server_send(protocol_t *self, char *buf){
    return socket_send(self->client_skt, buf, MAX_RESPONSE_LENGTH);
}

ssize_t protocol_server_receive(protocol_t *self, char *buf){
    if (!self->client_skt) {
        int client_skt = socket_accept(self->skt);
        self->client_skt = malloc(sizeof(socket_t));
        socket_init(self->client_skt, client_skt);
    }
    return socket_receive(self->client_skt, buf, MAX_REQUEST_LENGTH);
}


void protocol_release(protocol_t *self){
    socket_release(self->skt);
    free(self->skt);
    socket_release(self->client_skt);
    free(self->client_skt);
}

bool protocol_client_init(protocol_t *self, char* host, char *port) {
    socket_t *socket = malloc(sizeof(socket_t));
    if (!socket_init(socket, 0)) return false;
    if (!socket_connect(socket, host, port)) return false;
    self->skt = socket;
    self->client_skt = malloc(sizeof(socket_t));
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
