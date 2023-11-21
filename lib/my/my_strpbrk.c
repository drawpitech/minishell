/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strpbrk
*/

#include <stddef.h>
#include <string.h>

#include "my.h"

char *my_strfind(char *str, char c)
{
    if (str == NULL)
        return NULL;
    for (size_t i = 0; str[i]; i++)
        if (str[i] == c)
            return str + i;
    return NULL;
}

char *my_strpbrk(char *str, char const *chars)
{
    char *ptr = NULL;
    char *tmp = NULL;

    if (str == NULL || chars == NULL)
        return NULL;
    for (size_t i = 0; chars[i]; i++) {
        tmp = my_strfind(str, chars[i]);
        if (ptr == NULL || tmp < ptr)
            ptr = tmp;
    }
    return ptr;
}
