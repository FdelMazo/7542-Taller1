#ifndef TP1_SUDOKU_H
#define TP1_SUDOKU_H

#include "sudoku/board.h"
#include <stdlib.h>

#define SUDOKU_RANGE 9

typedef struct {
	board_t *board;
} sudoku_t;

void sudoku_init(sudoku_t *self);

void sudoku_load(sudoku_t *self, char *filename, size_t length);

void sudoku_put(sudoku_t *self, size_t number, size_t row, size_t column);

bool sudoku_verify(sudoku_t *self);

void sudoku_get(sudoku_t *self);

void sudoku_reset(sudoku_t *self);

#endif