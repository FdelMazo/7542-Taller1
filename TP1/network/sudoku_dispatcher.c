#include "sudoku_dispatcher.h"

void _sudoku_dispatcher_verify(sudoku_t* sudoku, char *command, char *output);
void _sudoku_dispatcher_reset(sudoku_t* sudoku, char *command, char *output);
void _sudoku_dispatcher_put(sudoku_t* sudoku, char *command, char *output);
void _sudoku_dispatcher_get(sudoku_t* sudoku, char *command, char *output);

void sudoku_dispatcher_command(sudoku_t* sudoku, char *command, char *output){
    if (command[0] == 'P') {
        sudoku_get(sudoku, output);
    }
    return;
}
