#include "cell.h"

void cell_init(cell_t *self) {
    self->original = false;
    self->number = 0;
}

bool cell_set_number(cell_t *self, uint8_t n) {
    if (self->original) return false;
    self->number = n;
    return true;
}

uint8_t cell_get_number(cell_t *self) {
    return self->number;
}

void cell_set_as_original(cell_t *self) {
    self->original = true;
}

char cell_repr(cell_t *self) {
    if (self->number == 0) return EMPTY_CELL;
    return '0' + (int) self->number;
}

