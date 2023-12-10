/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strcat
*/

#include "string.h"

char *my_strcat(char *dest, char const *src)
{
    size_t len;
    size_t i = 0;

    if (dest == NULL || src == NULL)
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

    if (dest == NULL || src == NULL)
        return NULL;
    len = my_strlen(dest);
    for (i = 0; src[i] && i < n; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return dest;
}

char *my_strapp(char **dest, char const *src)
{
    if (dest == NULL || *dest == NULL || src == NULL)
        return NULL;
    my_strcpy(*dest, src);
    *dest += my_strlen(src);
    return *dest;
}
