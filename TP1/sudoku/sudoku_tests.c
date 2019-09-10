#include "sudoku.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

//int main() {
void sudoku_tests() {
    sudoku_t sudoku;
    sudoku_init(&sudoku);

    printf("tests sudoku_load\n");
    assert(sudoku_load(&sudoku, "null.txt") == false);
    assert(sudoku_load(&sudoku, "board.txt") == true);

    printf("tests sudoku_put\n");
    assert(sudoku_put(&sudoku, 1, 1, 2) == 0);
    assert(sudoku_put(&sudoku, 1, 1, 2) == 0);
    assert(sudoku_put(&sudoku, 1, 10, 1) == 1);
    assert(sudoku_put(&sudoku, 1, 1, 10) == 1);
    assert(sudoku_put(&sudoku, 1, 0, 1) == 1);
    assert(sudoku_put(&sudoku, 1, 0, 0) == 1);
    assert(sudoku_put(&sudoku, 1, 1, 0) == 1);
    assert(sudoku_put(&sudoku, 10, 5, 5) == 2);
    assert(sudoku_put(&sudoku, 0, 1, 1) == 2);
    assert(sudoku_put(&sudoku, 1, 1, 1) == -1);

    sudoku_reset(&sudoku);

    printf("tests sudoku_verify\n");
    assert(sudoku_verify(&sudoku) == true);
    sudoku_put(&sudoku, 7, 5, 8);
    assert(sudoku_verify(&sudoku) == true);
    sudoku_put(&sudoku, 1, 1, 2);
    assert(sudoku_verify(&sudoku) == false);
    sudoku_put(&sudoku, 1, 1, 1);
    assert(sudoku_verify(&sudoku) == false);

    char *buf = calloc(800, 1);
    sudoku_get(&sudoku, buf);
    printf("%s", buf);
    free(buf);

    sudoku_release(&sudoku);
}

