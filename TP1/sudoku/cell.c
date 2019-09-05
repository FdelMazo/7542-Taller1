#include "cell.h"
#include <stdlib.h>

void cell_init(cell_t *self, uint8_t row, uint8_t col) {
    self->col = col;
    self->row = row;
    self->original = false;
    self->number = 0;
}

bool cell_set_number(cell_t *self, uint8_t n) {
	if (self->original) return false;
	self->number = n;
	return true;
}

void cell_set_as_original(cell_t *self) {
    self->original = true;
}

