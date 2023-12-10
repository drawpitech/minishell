/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** mem
*/

#include "string.h"

void *my_memset(void *s, int c, size_t n)
{
    uint8_t *p = s;

    for (size_t i = 0; i != n; ++i) {
        p[i] = c;
    }
    return s;
}

void *my_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
    uint8_t *ptrd = dest;
    const uint8_t *ptrs = src;

    for (size_t i = 0; i < n; i++)
        ptrd[i] = ptrs[i];
    return dest;
}

bool my_memassert(const void *got, const void *expect, size_t n)
{
    const uint8_t *ptr_a = got;
    const uint8_t *ptr_b = expect;

    for (size_t i = 0; i < n; i++)
        if (ptr_a[i] != ptr_b[i])
            return false;
    return true;
}

size_t my_memfind(const void *arr, const void *target, size_t n)
{
    const uint8_t *ptr = arr;

    for (size_t i = 0; true; i += n)
        if (my_memassert(ptr + i, target, n))
            return i;
}
