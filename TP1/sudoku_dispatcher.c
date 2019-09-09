#include "sudoku_dispatcher.h"
#include <stdio.h>
#include <string.h>

void _sudoku_dispatcher_get(sudoku_t *sudoku, char *output) {
    sudoku_get(sudoku, output);
}

void _sudoku_dispatcher_verify(sudoku_t *sudoku, char *output) {
    if (sudoku_verify(sudoku))
        snprintf(output, strlen(OK) + 1, OK);
    else
        snprintf(output, strlen(ERROR) + 1, ERROR);
}

void _sudoku_dispatcher_reset(sudoku_t *sudoku, char *output) {
    sudoku_reset(sudoku);
    sudoku_get(sudoku, output);
}

void _sudoku_dispatcher_put(sudoku_t *sudoku, char *command, char *output) {
    uint8_t n = command[1] - '0';
    size_t row = command[2] - '0';
    size_t col = command[3] - '0';
    int r = sudoku_put(sudoku, n, row, col);
    switch (r) {
        case 0:
            sudoku_get(sudoku, output);
            break;
        case 1:
            snprintf(output, strlen(INDEX) + 1, INDEX);
            break;
        case 2:
            snprintf(output, strlen(VALUE) + 1, VALUE);
            break;
        case 3:
            snprintf(output, strlen(ORIGINAL) + 1, ORIGINAL);
            break;
    }
}

void sudoku_dispatcher_command(sudoku_t *sudoku, char *command, char *output) {
    switch (command[0]) {
        case 'P':
            _sudoku_dispatcher_put(sudoku, command, output);
            break;
        case 'G':
            _sudoku_dispatcher_get(sudoku, output);
            break;
        case 'R':
            _sudoku_dispatcher_reset(sudoku, output);
            break;
        case 'V':
            _sudoku_dispatcher_verify(sudoku, output);
            break;
    }
    return;
}
