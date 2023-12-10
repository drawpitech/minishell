/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** swap
*/

#include "std.h"

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
