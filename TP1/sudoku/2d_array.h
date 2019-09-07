#ifndef TP1_2D_ARRAY_H
#define TP1_2D_ARRAY_H

#include <stdbool.h>
#include <stdio.h>

void _2d_array_destroy(void **arr);
void _2d_array_release(void ***arr);
bool _2d_array_init(void ***arr, size_t size, size_t n, size_t m);
void ***_2d_array_create(size_t n, size_t m);
#endif //TP1_2D_ARRAY_H
