/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** dprintf
*/

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>

#include "../my_printf.h"
#include "my.h"

size_t my_vdprintf(
    int fd,
    const char *restrict format,
    va_list ap)
{
    char *buf = NULL;
    size_t size = my_vasprintf(&buf, format, ap);

    write(fd, buf, size);
    free(buf);
    return size;
}

size_t my_dprintf(
    int fd,
    const char *restrict format,
    ...)
{
    va_list ap;
    size_t size = 0;

    if (format == NULL)
        return my_dprintf(fd, "(null)");
    va_start(ap, format);
    size = my_vdprintf(fd, format, ap);
    va_end(ap);
    return size;
}
