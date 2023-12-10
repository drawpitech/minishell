/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_strcmp
*/

#include "string.h"

int my_strcmp(char const *s1, char const *s2)
{
    size_t i = 0;

    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    if (s1[i] != s2[i])
        return s1[i] - s2[i];
    return 0;
}

int my_strncmp(char const *s1, char const *s2, size_t n)
{
    size_t i = 0;

    if (!s1 || !s2 || n == 0)
        return 0;
    while (i < n - 1 && s1[i]) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
