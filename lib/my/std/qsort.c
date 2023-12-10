/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** qsort
*/

#include "std.h"

static
size_t get_pivot(uint8_t *ptr, size_t nmemb, size_t size, compar_func_t *cmp)
{
    uint8_t *pivot = ptr + (nmemb - 1) * size;
    size_t i = 0;

    for (uint8_t *j = ptr; j < pivot; j += size) {
        if (cmp(j, pivot) < 0) {
            my_swap(ptr + (i * size), j, size);
            i += 1;
        }
    }
    my_swap(ptr + (i * size), pivot, size);
    return i;
}

void my_qsort(void *arr, size_t nmemb, size_t size, compar_func_t *compar)
{
    uint8_t *ptr = arr;
    size_t pi;

    if (nmemb <= 1)
        return;
    pi = get_pivot(ptr, nmemb, size, compar);
    my_qsort(ptr, pi, size, compar);
    my_qsort(ptr + (pi + 1) * size, nmemb - (pi + 1), size, compar);
}
