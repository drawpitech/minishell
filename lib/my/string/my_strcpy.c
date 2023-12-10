/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strcpy
*/

#include "string.h"

char *my_strcpy(char *dest, char const *src)
{
    size_t len = my_strlen(src);

    for (size_t i = 0; i < len; i++)
        dest[i] = src[i];
    dest[len] = '\0';
    return dest;
}

char *my_strncpy(char *dest, char const *src, size_t n)
{
    for (size_t i = 0; i < n; i++)
        dest[i] = src[i];
    return dest;
}
