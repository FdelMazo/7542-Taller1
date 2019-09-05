#ifndef TP1_SUDOKU_H
#define TP1_SUDOKU_H

#include <stdlib.h>
#include "board.h"

#define SUDOKU_RANGE 9
#define SUDOKU_SECTION 3

typedef struct {
    board_t *board;
} sudoku_t;

// Initializes sudoku structure
// Returns false if any of the heap allocations fail, otherwise, returns true
bool sudoku_init(sudoku_t *self);

// Loads the original cells to play, from a given file
// The file must be formatted as 9 lines of numbers, separated by spaces, with a 0 when a cell is to be left empty
// Returns false if fopen or any allocation fails, otherwise, returns true
bool sudoku_load(sudoku_t *self, char *filename);

// Writes n in the position (row,col)
// (row,col) are indexes from 1 to SUDOKU_RANGE
// n is a number from 1 to SUDOKU_RANGE
// Returns:
//   0 if the number was written
//   1 if (row,col) isn't in the supported range
//   2 if the number isn't in the supported range
//   3 if the cell is an original one
int sudoku_put(sudoku_t *self, size_t n, size_t row, size_t col);

// Verifys the status of the board
// A board is valid if it doesn't have any repeated numbers in the rows, columns, or sections
//   (which isn't to say it is mistake-free)
// A board isn't valid otherwise
// Returns true if the board is valid, false if it isn't
bool sudoku_verify(sudoku_t *self);

// Stores in the buf (of size _count_) a printable representation of the board
// If buf isn't long enough to store the string, returns -1
// Otherwise, returns the buf size
ssize_t sudoku_get(sudoku_t *self, char *buf, size_t count);

// Restores the board to the original one, without the user-modified cells
void sudoku_reset(sudoku_t *self);

#endif
