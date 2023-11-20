/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** mem
*/

#include <stdint.h>
#include <stdlib.h>

#include "my.h"

void my_swap(void *left, void *right, size_t size)
{
    uint8_t *l_ptr = left;
    uint8_t *r_ptr = right;
    uint8_t tmp;

    for (uint32_t i = 0; i < size; i++) {
        tmp = l_ptr[i];
        l_ptr[i] = r_ptr[i];
        r_ptr[i] = tmp;
    }
}

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
