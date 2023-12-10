/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** str_identify
*/

#include "string.h"

bool my_str_isnum(char const *str)
{
    for (size_t i = 0; str[i]; i++)
        if (!IS_NUM(str[i]))
            return false;
    return true;
}

bool my_str_isupper(char const *str)
{
    for (size_t i = 0; str[i]; i++)
        if (!IS_UPPERCASE(str[i]))
            return false;
    return true;
}

bool my_str_islower(char const *str)
{
    for (size_t i = 0; str[i]; i++)
        if (!IS_LOWERCASE(str[i]))
            return false;
    return true;
}

bool my_str_isalpha(char const *str)
{
    for (size_t i = 0; str[i]; i++)
        if (!IS_ALPHA(str[i]))
            return false;
    return true;
}

bool my_str_isprintable(char const *str)
{
    for (size_t i = 0; str[i]; i++)
        if (!IS_PRINTABLE(str[i]))
            return false;
    return true;
}
