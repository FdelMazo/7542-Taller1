#include "cell.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "2d_array.h"

bool board_init(board_t *self, size_t range, size_t division) {
    cell_t ***cells;
    cells = (cell_t***) _2d_array_create(range, range);
    if (!cells) return false;

    if (!_2d_array_init((void ***) cells, sizeof(cell_t), range, range)) {
        _2d_array_release((void ***) cells);
        return false;
    }

    for (size_t row=0; row<range; row++){
        for (size_t col=0; col<range; col++){
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

bool _board_verify_cells_set(board_t *self, size_t row_i, size_t row_f,
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

bool _board_verify_row(board_t *self, size_t row) {
    size_t row_i = row;
    size_t row_f = row;
    size_t col_i = 0;
    size_t col_f = self->range;
    return _board_verify_cells_set(self, row_i, row_f, col_i, col_f);
}


bool _board_verify_column(board_t *self, size_t col) {
    size_t row_i = 0;
    size_t row_f = self->range;
    size_t col_i = col;
    size_t col_f = col;
    return _board_verify_cells_set(self, row_i, row_f, col_i, col_f);
}


bool _board_verify_section(board_t *self, size_t sec) {
    size_t row_i = floor(sec / self->division) * self->division;
    size_t row_f = row_i + self->division;
    size_t col_i = (sec % self->division) * self->division;
    size_t col_f = col_i + self->division;
    return _board_verify_cells_set(self, row_i, row_f, col_i, col_f);
}


bool board_verify(board_t *self) {
    for (size_t n = 0; n < self->range; n++) {
        if (!_board_verify_row(self, n)) return false;
        if (!_board_verify_column(self, n)) return false;
        if (!_board_verify_section(self, n)) return false;
    }
    return true;
}

bool _board_repr_cell(board_t *self, char *buf, ssize_t row, size_t col) {
    char *cell_buf = calloc(CELL_LEN+1, sizeof(char));
    if (!(cell_buf)) return false;

    if (row == -1)
        memset(cell_buf, HEADER, CELL_LEN);
    else if (row == -2)
        memset(cell_buf, CELL_TOP, CELL_LEN);
    else
        snprintf(cell_buf, CELL_LEN+1, CELL_FORMAT,
                 cell_repr(self->cells[row][col]));

    strncat(buf, cell_buf, CELL_LEN);
    free(cell_buf);
    return true;
}

bool _board_repr_cells(board_t *self, char *buf, ssize_t row, size_t col_i) {
    snprintf(buf, sizeof(char)*2, "%s", COLUMN);
    size_t col_f = col_i + self->division;
    for (size_t col = col_i; col < col_f; col++) {
        if (!_board_repr_cell(self, buf, row, col))
            return false;
    }

    return true;
}
bool _board_repr_row(board_t *self, char *buf, ssize_t row) {
    for (size_t cells = 0; cells < self->division; cells++) {
        char *cells_buf;
        size_t cell_len = strlen(CELL_FORMAT) +1;
        size_t cells_len = (cell_len + strlen(COLUMN)) * self->division;
        if (!(cells_buf = calloc(cells_len, sizeof(char)))) return false;
        if (!(_board_repr_cells(self, cells_buf, row, cells * self->division)))
            return false;
        strncat(buf, cells_buf, strlen(cells_buf));
        free(cells_buf);
    }
    strncat(buf, COLUMN, strlen(COLUMN));
    strncat(buf, "\n", strlen("\n"));
    return true;
}

bool board_repr(board_t *self, char *buf) {
    size_t cell_len = strlen(CELL_FORMAT) +1;
    size_t cells_len = (cell_len + strlen(COLUMN)) * self->division;
    size_t row_len = (cells_len + strlen(COLUMN)) * self->division;

    for (size_t i = 0; i < self->range; i++) {
        char *row_buf;

        if (!(row_buf = calloc(row_len, sizeof(char)))) return false;

        if ((i % self->division) == 0) {
            char *header;
            if (!(header = calloc(row_len, sizeof(char)))) return false;
            _board_repr_row(self, header, -1);
            strncat(buf, header, strlen(header));
            free(header);
        } else {
            char *separator;
            if (!(separator = calloc(row_len, sizeof(char)))) return false;
            _board_repr_row(self, separator, -2);
            strncat(buf, separator, strlen(separator));
            free(separator);
        }
        _board_repr_row(self, row_buf, i);
        strncat(buf, row_buf, strlen(row_buf));
        free(row_buf);
    }
    char *footer;
    if (!(footer = calloc(row_len, sizeof(char)))) return false;
    _board_repr_row(self, footer, -1);
    strncat(buf, footer, strlen(footer));
    free(footer);
    return true;
}

void board_release(board_t *self) {
//    _2d_array_release((void ***) self->cells);
    _3d_array_destroy((void ***) self->cells);
}
