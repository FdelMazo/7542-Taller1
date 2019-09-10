#include "server.h"
#include "debug.h"
#include <stdio.h>
#include "sudoku_dispatcher.h"

int server_main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: ./tp server <puerto>\n");
        return 1;
    }
    server_t server;
    if (!server_init(&server, argv[2])) return 1;
    server_communicate(&server);
    server_release(&server);
    return 0;
}

bool server_init(server_t *self, char *port) {
    bool no_err = true;
    protocol_t *protocol = malloc(sizeof(protocol_t));
    sudoku_t *sudoku = malloc(sizeof(sudoku_t));
    no_err &= protocol_server_init(protocol, port);
    no_err &= sudoku_init(sudoku);
    no_err &= sudoku_load(sudoku, BOARD_PATH);
    self->protocol = protocol;
    self->sudoku = sudoku;

    if (!protocol || !sudoku || !no_err) {
        server_release(self);
        return false;
    }
    return true;
}

void server_communicate(server_t *self) {
    protocol_server_accept(self->protocol);
    while (true) {
        char command[REQUEST_LENGTH + ARGUMENTS_LENGTH] = {0};
        if (protocol_server_receive(self->protocol, command) <= 0) break;
//        DEBUG_PRINT("Server got: %s\n", command);
        char output[MAX_RESPONSE_LENGTH] = {0};
        sudoku_dispatcher_command(self->sudoku, command, output);
        protocol_server_send(self->protocol, output);
//        DEBUG_PRINT("Server sending back: \n%s\n", output);
    }
}

void server_release(server_t *self) {
    if (!self) return;
    protocol_release(self->protocol);
    free(self->protocol);
    sudoku_release(self->sudoku);
    free(self->sudoku);
}
