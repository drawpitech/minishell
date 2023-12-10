/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** strcases
*/

#include "string.h"

char *my_strupcase(char *str)
{
    for (size_t i = 0; str[i]; i++)
        str[i] = CH_UPP(str[i]);
    return str;
}

char *my_strlowcase(char *str)
{
    for (size_t i = 0; str[i]; i++)
        str[i] = CH_LOW(str[i]);
    return str;
}

char *my_strcapitalize(char *str)
{
    int on_word = 0;

    for (int i = 0; str[i]; i++) {
        if (!IS_ALPHA(str[i]) && !IS_NUM(str[i])) {
            on_word = 0;
            continue;
        }
        if (IS_LOWERCASE(str[i]) && !on_word)
            str[i] -= 32;
        if (IS_UPPERCASE(str[i]) && on_word)
            str[i] += 32;
        on_word = 1;
    }
    return str;
}
