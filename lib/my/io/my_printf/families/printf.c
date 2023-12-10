/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** printf
*/

#include <unistd.h>

#include "io.h"

#include "../internal.h"

size_t my_vprintf(
    const char *restrict format,
    va_list ap)
{
    return my_vdprintf(STDOUT_FILENO, format, ap);
}

size_t my_printf(
    const char *restrict format,
    ...)
{
    va_list ap;
    size_t size = 0;

    if (format == NULL)
        return my_printf("(null)");
    va_start(ap, format);
    size = my_vprintf(format, ap);
    va_end(ap);
    return size;
}
