#ifndef TP1_BOARD_H
#define TP1_BOARD_H

#include "cell.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define CELL_TOP "-"
#define CELL_SIDE '|'
#define CELL_CORNER '+'
#define HEADER "="
#define COLUMN "U"

typedef struct {
    cell_t ***cells;
    size_t range;
    size_t division;
} board_t;

bool board_init(board_t *self, size_t range, size_t division);

bool board_set_number(board_t *self, uint8_t number, size_t row, size_t col);

void board_set_as_original(board_t *self, size_t row, size_t col);

void board_load(board_t *self, uint8_t **numbers, size_t rows, size_t columns);

void board_repr(board_t *self, char *buf);

void board_reset(board_t *self);

bool board_verify(board_t *self);

#endif
