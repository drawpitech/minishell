/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** char
*/

#include "string.h"

#include "../internal.h"

void printf_char(printf_t *pr, printf_args_t *arg)
{
    static char buffer[2] = {0};
    char c = (char)va_arg(pr->ap, int);

    buffer[0] = c;
    write_flag(pr, arg, buffer);
}

void printf_purcent(printf_t *pr, printf_args_t *arg)
{
    static char buffer[] = "%";

    write_flag(pr, arg, buffer);
}
