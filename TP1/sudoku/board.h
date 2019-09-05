#ifndef TP1_BOARD_H
#define TP1_BOARD_H

#include <stdint.h>
#include "cell.h"
#include <stdlib.h>

typedef struct {
    cell_t*** cells;
} board_t;

bool board_init(board_t *self);

bool board_set_number(board_t *self, size_t number, size_t row, size_t col);

void board_set_as_original(board_t *self, size_t row, size_t col);

void board_load(board_t *self, size_t **numbers, size_t rows, size_t columns);

size_t board_to_string(board_t *self, char *buf, size_t count);

void board_reset(board_t *self);

bool board_verify(board_t *self);

#endif