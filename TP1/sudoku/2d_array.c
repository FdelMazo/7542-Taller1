#include "2d_array.h"
#include <stdlib.h>

void ***_2d_array_create(size_t n, size_t m) {
    void ***arr;
    if (!(arr = calloc(n, sizeof(void *)))) return NULL;

    for (size_t x = 0; x < n; x++) {
        if (!(arr[x] = malloc(sizeof(void *) * m))) {
            _2d_array_destroy((void **) arr, n);
            return NULL;
        }
    }
    return arr;
}

bool _2d_array_init(void ***arr, size_t size, size_t n, size_t m) {
    for (size_t x = 0; x < n; x++) {
        for (size_t y = 0; y < m; y++) {
            void *elem;
            if (!(elem = malloc(size))) {
                return false;
            }
            arr[x][y] = elem;
        }
    }
    return true;
}

void _2d_array_release(void ***arr, size_t n, size_t m) {
    for (size_t x = 0; x < n; x++) {
        for (size_t y = 0; y < m; y++) free(arr[x][y]);
    }
}

void _2d_array_destroy(void **arr, size_t n) {
    for (size_t x = 0; x < n; x++)
        free(arr[x]);
    free(arr);
}
