#include "sudoku.h"
#include <stdlib.h>
#include <stdio.h>
#include "2d_array.h"


bool sudoku_init(sudoku_t *self) {
    board_t *board = malloc(sizeof(board_t));
    if (!(board) || !board_init(board, SUDOKU_RANGE, SUDOKU_DIVISION)) {
        free(board);
        return false;
    }

    self->board = board;
    return true;
}

bool sudoku_load(sudoku_t *self, char *filename) {
    FILE *stream;
    if (!(stream = fopen(filename, "r"))) return false;

    uint8_t **numbers;
    numbers = (uint8_t **) _2d_array_create(SUDOKU_RANGE, SUDOKU_RANGE);
    if (!numbers) {
        fclose(stream);
        return false;
    }

    for (size_t n_line = 0; n_line < SUDOKU_RANGE; n_line++) {
        for (size_t i = 0; i < SUDOKU_RANGE; i++) {
            int n;
            if (!fscanf(stream, "%d", &n)) continue;
            numbers[n_line][i] = n;
        }
    }

    board_load(self->board, numbers, SUDOKU_RANGE, SUDOKU_RANGE);
    _2d_array_destroy((void **) numbers);
    fclose(stream);
    return true;
}

int sudoku_put(sudoku_t *self, size_t n, size_t row, size_t col) {
    if (row <= 0 || col <= 0 || row > SUDOKU_RANGE || col > SUDOKU_RANGE)
        return 1;
    if (n == 0 || n > SUDOKU_RANGE)
        return 2;
    if (!board_set_number(self->board, n, row - 1, col - 1))
        return 3;
    return 0;
}

bool sudoku_verify(sudoku_t *self) {
    return board_verify(self->board);
}

void sudoku_get(sudoku_t *self, char *buf) {
    board_repr(self->board, buf);
}

void sudoku_reset(sudoku_t *self) {
    board_reset(self->board);
}

void sudoku_release(sudoku_t *self) {
    board_release(self->board);
    free(self->board);
}
