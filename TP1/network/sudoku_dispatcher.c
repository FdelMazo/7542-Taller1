#include "sudoku_dispatcher.h"
#include <stdio.h>
#include <string.h>

bool sudoku_dispatcher_input_valid(uint8_t n, size_t row, size_t col) {
    switch (sudoku_put_valid(n, row, col)) {
        case 1:
            fprintf(stderr, INDEX_ERR);
            return false;
        case 2:
            fprintf(stderr, VALUE_ERR);
            return false;
    }
    return true;
}

static void _get(sudoku_t *sudoku, char *output) {
    sudoku_get(sudoku, output);
}

static void _verify(sudoku_t *sudoku, char *output) {
    if (sudoku_verify(sudoku))
        snprintf(output, strlen(OK) + 1, OK);
    else
        snprintf(output, strlen(ERROR) + 1, ERROR);
}

static void _reset(sudoku_t *sudoku, char *output) {
    sudoku_reset(sudoku);
    sudoku_get(sudoku, output);
}

static void _put(sudoku_t *sudoku, char *command, char *output) {
    uint8_t n = command[1] - '0';
    size_t row = command[2] - '0';
    size_t col = command[3] - '0';
    if ((sudoku_put(sudoku, n, row, col)) == -1) {
        snprintf(output, strlen(ORIGINAL_CELL_ERR) + 1, ORIGINAL_CELL_ERR);
        return;
    }
    sudoku_get(sudoku, output);
}

void sudoku_dispatcher_command(sudoku_t *sudoku, char *command, char *output) {
    switch (command[0]) {
        case 'P':
            _put(sudoku, command, output);
            break;
        case 'G':
            _get(sudoku, output);
            break;
        case 'R':
            _reset(sudoku, output);
            break;
        case 'V':
            _verify(sudoku, output);
            break;
    }
    return;
}
