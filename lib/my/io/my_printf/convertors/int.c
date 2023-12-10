/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** int
*/

#include "string.h"

#include "../internal.h"

void printf_int(printf_t *pr, printf_args_t *arg)
{
    static char buffer[12] = {0};
    size_t size = 0;
    int nbr = va_arg(pr->ap, int);

    my_memset(buffer, 0, 12);
    if (arg->flags.sign) {
        buffer[0] = (nbr >= 0) ? '+' : '-';
        size += 1;
    } else if (arg->flags.space && nbr >= 0) {
        buffer[0] = ' ';
        size += 1;
    }
    write_int_base(nbr, BASE_DEC, buffer + size);
    write_flag(pr, arg, buffer);
}
