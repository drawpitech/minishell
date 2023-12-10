/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** len
*/

#include "string.h"
#include "std.h"

#include "../internal.h"

void printf_len(printf_t *pr, ATTR(unused) printf_args_t *arg)
{
    size_t *size = va_arg(pr->ap, size_t *);

    *size = pr->buf.size;
}
