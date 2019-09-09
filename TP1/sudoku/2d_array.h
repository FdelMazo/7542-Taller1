#ifndef TP1_2D_ARRAY_H
#define TP1_2D_ARRAY_H

#include <stdbool.h>
#include <stdio.h>

void ***_2d_array_create(size_t n, size_t m);

bool _2d_array_init(void ***arr, size_t size, size_t n, size_t m);

void _2d_array_release(void ***arr);

void _2d_array_destroy(void **arr);

#endif //TP1_2D_ARRAY_H
