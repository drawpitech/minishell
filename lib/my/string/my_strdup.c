/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strdup
*/

#include "string.h"
#include "std.h"

char *my_strdup(char const *src)
{
    char *dest;

    if (!src)
        return NULL;
    dest = malloc((my_strlen(src) + 1) * sizeof(char));
    if (!dest)
        return NULL;
    my_strcpy(dest, src);
    return dest;
}

char *my_strndup(char const *src, size_t n)
{
    char *dest;

    if (!src)
        return NULL;
    dest = malloc((n + 1) * sizeof(char));
    if (dest == NULL)
        return NULL;
    my_strncpy(dest, src, n);
    return dest;
}
