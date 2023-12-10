/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** ptr
*/

#include "string.h"

#include "../internal.h"

void printf_pointer(printf_t *pr, printf_args_t *arg)
{
    static char buffer[23] = {0};
    unsigned long ptr = (unsigned long)va_arg(pr->ap, void *);

    my_strcpy(buffer, "0x");
    write_uint_base(ptr, BASE_HEX_MIN, buffer + 2);
    write_flag(pr, arg, buffer);
}
