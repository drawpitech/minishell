/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strcat
*/

#include <stddef.h>

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    size_t len;
    size_t i = 0;

    if (!dest || !src)
        return NULL;
    len = my_strlen(dest);
    for (; src[i]; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}

char *my_strncat(char *dest, char const *src, size_t n)
{
    size_t len;
    size_t i;

    if (!dest || !src)
        return NULL;
    len = my_strlen(dest);
    for (i = 0; src[i] && i < n; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}
