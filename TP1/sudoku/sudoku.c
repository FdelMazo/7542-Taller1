#include "sudoku.h"
#include "aux/strutil.h"
#include <stdlib.h>
#include <stdio.h>

void sudoku_init(sudoku_t *self){
    board_t *board = malloc(sizeof(board_t));
    board_init(board);
    self->board = board;
}

void sudoku_load(sudoku_t *self, char *filename, size_t length) {
    FILE *stream = fopen(filename, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    size_t n_line = 0;

    size_t **numbers = malloc(sizeof(size_t) * 9 * 9);

    for (int row=0; row<9; row++){
        numbers[row] = malloc(sizeof(size_t) * 9);
    }

    while ((nread = getline(&line, &len, stream)) != -1) {
        char** numbers_in_line = split(line, ' ');
        for (size_t i = 0; numbers_in_line[i]; i++) {
            size_t n = atoi(numbers_in_line[i]);
            numbers[n_line][i] = n;
        }

        n_line++;
    }
    free(line);

    board_load(self->board, numbers, 9, 9);
}

void sudoku_put(sudoku_t *self, size_t number, size_t row, size_t col) {
    board_set_number(self->board, number, row, col);
}

bool sudoku_verify(sudoku_t *self) {
//    bool board_verify(self->board);
    return true;
}

void sudoku_get(sudoku_t *self) {
    board_to_string(self->board);
}

void sudoku_reset(sudoku_t *self) {
    board_reset(self->board);
}
