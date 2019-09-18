#include "cell.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "2d_array.h"

bool board_init(board_t *self, size_t range, size_t division) {
    cell_t ***cells;
    cells = (cell_t ***) _2d_array_create(range, range);
    if (!cells) return false;

    if (!_2d_array_init((void ***) cells, sizeof(cell_t), range, range)) {
        _2d_array_release((void ***) cells, range, range);
        return false;
    }

    for (size_t row = 0; row < range; row++) {
        for (size_t col = 0; col < range; col++) {
            cell_init(cells[row][col]);
        }
    }
    self->cells = cells;
    self->division = division;
    self->range = range;
    return true;
}

void board_load(board_t *self, uint8_t **numbers, size_t rows, size_t columns) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < columns; col++) {
            if (numbers[row][col]) {
                board_set_number(self, numbers[row][col], row, col);
                board_set_as_original(self, row, col);
            }
        }
    }
}

bool board_set_number(board_t *self, uint8_t n, size_t row, size_t col) {
    return cell_set_number(self->cells[row][col], n);
}

void board_set_as_original(board_t *self, size_t row, size_t col) {
    cell_set_as_original(self->cells[row][col]);
}

void board_reset(board_t *self) {
    for (size_t row = 0; row < self->range; row++) {
        for (size_t col = 0; col < self->range; col++) {
            cell_set_number(self->cells[row][col], 0);
        }
    }
}

static bool _verify_cells_set(board_t *self, size_t row_i, size_t row_f,
                              size_t col_i, size_t col_f) {
    bool *numbers = calloc(sizeof(bool), self->range);
    for (size_t row = row_i; row < row_f; row++) {
        for (size_t col = col_i; col < col_f; col++) {
            int n = cell_get_number(self->cells[row][col]);
            if (n == 0) continue;
            if (numbers[n - 1]) {
                free(numbers);
                return false;
            }
            numbers[n - 1] = true;
        }
    }
    free(numbers);
    return true;
}

static bool _verify_row(board_t *self, size_t row) {
    size_t row_i = row;
    size_t row_f = row +1;
    size_t col_i = 0;
    size_t col_f = self->range;
    return _verify_cells_set(self, row_i, row_f, col_i, col_f);
}


static bool _verify_column(board_t *self, size_t col) {
    size_t row_i = 0;
    size_t row_f = self->range;
    size_t col_i = col;
    size_t col_f = col +1;
    return _verify_cells_set(self, row_i, row_f, col_i, col_f);
}


static bool _verify_section(board_t *self, size_t sec) {
    size_t row_i = floor(sec / self->division) * self->division;
    size_t row_f = row_i + self->division;
    size_t col_i = (sec % self->division) * self->division;
    size_t col_f = col_i + self->division;
    return _verify_cells_set(self, row_i, row_f, col_i, col_f);
}


bool board_verify(board_t *self) {
    for (size_t n = 0; n < self->range; n++) {
        if (!_verify_row(self, n)) return false;
        if (!_verify_column(self, n)) return false;
        if (!_verify_section(self, n)) return false;
    }
    return true;
}

static ssize_t _repr_cell(board_t *self, char *buf, ssize_t row, size_t col) {
    ssize_t len = CELL_LEN + 2;
    char *cell_buf = calloc(len + 2, sizeof(char));
    char side_c;
    if (!(cell_buf)) return -1;

    if (row == -1) {
        memset(cell_buf, HEADER, CELL_LEN);
        side_c = HEADER_SIDE;
    } else if (row == -2) {
        memset(cell_buf, CELL_TOP, CELL_LEN);
        side_c = CELL_CORNER;
    } else {
        len = snprintf(cell_buf, len + 1, CELL_FORMAT,
                       cell_repr(self->cells[row][col]));
        side_c = CELL_SIDE;
    }

    if ((col % self->division) != self->division - 1) {
        char side[] = {side_c, 0};
        strncat(cell_buf, side, strlen(side));
        len += strlen(side);
    }

    strncat(buf, cell_buf, len);
    free(cell_buf);
    return len;
}

static ssize_t _repr_cells(board_t *self, char *buf,
                           ssize_t row, size_t col_i) {
    char column[] = {COLUMN, 0};
    strncat(buf, column, strlen(column));
    ssize_t len = 0;
    size_t col_f = col_i + self->division;
    for (size_t col = col_i; col < col_f; col++) {
        len += _repr_cell(self, buf, row, col);
    }
    return len;
}

static ssize_t _repr_row(board_t *self, char *buf, size_t row) {
    ssize_t len = 0;
    for (size_t cells = 0; cells < self->division; cells++) {
        len += _repr_cells(self, buf, row, cells * self->division);
    }
    char column[] = {COLUMN, '\n'};
    strncat(buf, column, strlen(column));
    return len;
}

void board_repr(board_t *self, char *buf) {
    for (size_t i = 0; i < self->range; i++) {
        if ((i % self->division) == 0)
            _repr_row(self, buf, -1);
        else
            _repr_row(self, buf, -2);
        _repr_row(self, buf, i);
    }
    _repr_row(self, buf, -1);
}

void board_release(board_t *self) {
    _2d_array_release((void ***) self->cells, self->range, self->range);
    _2d_array_destroy((void **) self->cells, self->range);
}
