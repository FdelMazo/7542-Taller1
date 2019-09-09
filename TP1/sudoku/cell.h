#ifndef TP1_CELL_H
#define TP1_CELL_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define EMPTY_CELL ' '

typedef struct {
    bool original;
    uint8_t number;
} cell_t;

void cell_init(cell_t *self);

bool cell_set_number(cell_t *self, uint8_t n);

uint8_t cell_get_number(cell_t *self);

void cell_set_as_original(cell_t *self);

char cell_repr(cell_t *self);

#endif
