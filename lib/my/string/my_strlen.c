/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strlen
*/

#include "string.h"

size_t my_strlen(char const *str)
{
    size_t len = 0;

    if (str == NULL)
        return 0;
    for (; str[len]; len++);
    return len;
}
