#include "sudoku_dispatcher.h"
#include <stdio.h>

void _sudoku_dispatcher_get(sudoku_t *sudoku, char *output) {
    sudoku_get(sudoku, output);
}

void _sudoku_dispatcher_verify(sudoku_t *sudoku, char *output) {
    if (sudoku_verify(sudoku))
        sprintf(output, "OK\n");
    else
        sprintf(output, "ERROR\n");
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
            sprintf(output, "Error en los índices. Rango soportado: [1,9]\n");
            break;
        case 2:
            sprintf(output, "Error en el valor ingresado. Rango soportado:: [1,9]\n");
            break;
        case 3:
            sprintf(output, "La celda indicada no es modificable\n");
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
