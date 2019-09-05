#include "sudoku.h"
#include "../aux/strutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

bool sudoku_init(sudoku_t *self) {
    board_t *board = malloc(sizeof(board_t));
    if (!board || !board_init(board)) {
        free(board);
        return false;
    }

    self->board = board;
    return true;
}

bool sudoku_load(sudoku_t *self, char *filename) {
    FILE *stream;
    if (!(stream = fopen(filename, "r"))) {
        fprintf(stderr, "sudoku_load-->fopen: %s\n", strerror(errno));
        return false;
    }

    char *line = NULL;
    size_t len = 0;

    size_t **numbers = malloc(sizeof(size_t) * SUDOKU_RANGE * SUDOKU_RANGE);
    if (!numbers) {
        fclose(stream);
        return false;
    }

    for (size_t row = 0; row < SUDOKU_RANGE; row++) {
        numbers[row] = malloc(sizeof(size_t) * SUDOKU_RANGE);

        if (!numbers[row]) {
            for (size_t i = 0; numbers[i]; i++)
                free(numbers[i]);
            free(numbers);
            fclose(stream);
            return false;
        }
    }

    for (size_t n_line = 0; n_line < SUDOKU_RANGE && (getline(&line, &len, stream) != -1); n_line++) {
        char **numbers_in_line = split(line, ' ');
        for (size_t i = 0; numbers_in_line[i]; i++) {
            size_t n = atoi(numbers_in_line[i]);
            numbers[n_line][i] = n;
        }

    }
    free(line);

    board_load(self->board, numbers, SUDOKU_RANGE, SUDOKU_RANGE);
    fclose(stream);
    return true;
}

int sudoku_put(sudoku_t *self, size_t n, size_t row, size_t col) {
    if (row <= 0 || col <= 0 || row > SUDOKU_RANGE || col > SUDOKU_RANGE)
        return 1;
    if (n == 0 || n > SUDOKU_RANGE)
        return 2;
    size_t row_index = row - 1;
    size_t col_index = col - 1;
    if (!board_set_number(self->board, n, row_index, col_index))
        return 3;
    return 0;
}

bool sudoku_verify(sudoku_t *self) {
    return board_verify(self->board);
}

ssize_t sudoku_get(sudoku_t *self, char *buf, size_t count) {
    return board_to_string(self->board, buf, count);
}

void sudoku_reset(sudoku_t *self) {
    board_reset(self->board);
}
