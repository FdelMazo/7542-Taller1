#include "sudoku.h"

int main() {
    sudoku_t sudoku;
    sudoku_init(&sudoku);
    sudoku_load(&sudoku, "resources/board.txt", 20);
    sudoku_get(&sudoku);
}
