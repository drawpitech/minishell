/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** reverse
*/

#include "std.h"
#include "string.h"

void *reverse_arr(uint32_t size, void *arr, size_t memsize)
{
    uint8_t *ptr = arr;

    for (uint32_t i = 0; i < size / 2; i++)
        my_swap(ptr + i * memsize, ptr + (size - i - 1) * memsize, memsize);
    return arr;
}

char *my_revstr(char *src)
{
    return (char *)reverse_arr(my_strlen(src), src, sizeof(char));
}
