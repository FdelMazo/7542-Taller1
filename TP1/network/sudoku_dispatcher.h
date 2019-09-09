#ifndef TP1_SUDOKU_DISPATCHER_H
#define TP1_SUDOKU_DISPATCHER_H

#include "sudoku.h"

#define OK "OK\n"
#define ERROR "ERROR\n"
#define ORIGINAL_CELL_ERR "La celda indicada no es modificable\n"
#define INDEX_ERR "Error en los índices. Rango soportado: [1,9]\n"
#define VALUE_ERR "Error en el valor ingresado. Rango soportado: [1,9]\n"


// Used by client (inside the protocol)
// Receives a put command ('P123' == 'put 1 in 2,3')
// Responds whether it is valid or not
// Returns:
//   true if the command is valid
//   false if there was an error, and prints it
bool sudoku_dispatcher_input_valid(uint8_t n, size_t row, size_t col);

// Used by server
// Receives a command (which would be the client request)
//    and an empty output buffer (the server response)
// Applies the respective actions to the sudoku
// Fills the buffer with the corresponding response
void sudoku_dispatcher_command(sudoku_t *sudoku, char *command, char *output);

#endif //TP1_SUDOKU_DISPATCHER_H
