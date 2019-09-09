#ifndef TP1_SUDOKU_DISPATCHER_H
#define TP1_SUDOKU_DISPATCHER_H

#include "../sudoku/sudoku.h"

#define OK "OK\n"
#define ERROR "ERROR\n"
#define INDEX "Error en los índices. Rango soportado: [1,9]\n"
#define VALUE "Error en el valor ingresado. Rango soportado: [1,9]\n"
#define ORIGINAL "La celda indicada no es modificable\n"

void sudoku_dispatcher_command(sudoku_t *sudoku, char *command, char *output);

#endif //TP1_SUDOKU_DISPATCHER_H
