#include "cell.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>

void board_init(board_t *self) {
    cell_t ***cells = malloc(sizeof(cell_t) * 9 * 9);

    for (int row=0; row<9; row++){
        cells[row] = malloc(sizeof(cell_t) * 9);
    }

    for (int x=0; x<9; x++){
        for (int y=0; y<9; y++){
            cell_t *cell = malloc(sizeof(cell_t));
            cell_init(cell, x, y);
            cells[y][x] = cell;
        }
    }
    self->cells = cells;
}

void board_load(board_t *self, size_t **numbers, size_t rows, size_t columns) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < columns; col++) {
            if (numbers[row][col]) {
                board_set_number(self, numbers[row][col], row, col);
                board_set_as_original(self, row, col);
            }
        }
    }
}

void board_set_number(board_t *self, size_t n, size_t row, size_t col) {
    cell_set_number(self->cells[row][col], n);
}

void board_set_as_original(board_t *self, size_t row, size_t col) {
    cell_set_as_original(self->cells[row][col]);
}

void board_to_string(board_t *self) {
    printf("\n~~~\n");
    for (int x=0; x<9; x++){
        for (int y=0; y<9; y++){
            printf("%zd", self->cells[x][y]->number);
        }
        printf("\n");
    }
    printf("~~~\n");
}

void board_reset(board_t *self){
    for (int x=0; x<9; x++){
        for (int y=0; y<9; y++){
            cell_set_number(self->cells[x][y], 0);
        }
    }
}