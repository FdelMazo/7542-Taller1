#ifndef TP1_CELL_H
#define TP1_CELL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	bool original;
    size_t number;
	size_t row;
	size_t col;
} cell_t;

void cell_init(cell_t *self, uint8_t x, uint8_t y);
bool cell_set_number(cell_t *self, uint8_t n);
void cell_set_as_original(cell_t *self);

#endif