#include "server.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
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

bool server_init(server_t *self, char* port) {
    protocol_t *protocol = malloc(sizeof(protocol_t));;
    if (!protocol_server_init(protocol, port)) return false;
    self->protocol = protocol;

    sudoku_t* sudoku = malloc(sizeof(sudoku_t));
    if (!sudoku_init(sudoku)) return false;
    if (!sudoku_load(sudoku, BOARD_PATH)) return false;
    self->sudoku = sudoku;

    return true;
}

bool _server_exit(char *OUTPUT){
//    if (strncmp(OUTPUT, EXIT_COMMAND, strlen(EXIT_COMMAND)) == 0) return true;
    return false;
}


void server_communicate(server_t *self){
    char *command = calloc(MAX_LENGTH_COMMAND, sizeof(char));
    char* response = calloc(MAX_LENGTH_OUTPUT, sizeof(char));
    char* output = calloc(MAX_LENGTH_OUTPUT, sizeof(char));
    while (true) {
        protocol_server_receive(self->protocol, command);
        DEBUG_PRINT("server got: %s\n", command);
        sudoku_dispatcher_command(self->sudoku, command, output);
        protocol_server_send(self->protocol, output);
        DEBUG_PRINT("server sending back: %s\n", output);
        if (_server_exit(output)) {
            break;
        }
    }
    free(response);
    free(command);
    free(output);
}

void server_release(server_t *self) {
    protocol_release(self->protocol);
    sudoku_release(self->sudoku);
}
