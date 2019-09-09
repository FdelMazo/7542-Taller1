#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "protocol.h"
#include <stdbool.h>
#include "../sudoku/sudoku.h"

#define BOARD_PATH "board.txt"

typedef struct {
    protocol_t *protocol;
    sudoku_t *sudoku;
} server_t;

int server_main(int argc, char *argv[]);

bool server_init(server_t *self, char *port);

void server_communicate(server_t *self);

void server_release(server_t *self);

#endif //TP1_SERVER_H
