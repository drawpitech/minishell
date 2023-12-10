/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_showstr
*/

#include "io.h"
#include "string.h"

int my_showstr(char const *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if (IS_PRINTABLE(str[i])) {
            my_putchar(str[i]);
            continue;
        }
        my_putchar('\\');
        if (str[i] < 16)
            my_putchar('0');
        my_printf("%x", str[i]);
    }
    return 0;
}
