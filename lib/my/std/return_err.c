/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** return_err
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "std.h"
#include "io.h"

int ret_error(char const *format, ...)
{
    va_list ap;

    if (format == NULL)
        return ret_error("%s\n", strerror(errno));
    va_start(ap, format);
    my_vdprintf(STDERR_FILENO, format, ap);
    va_end(ap);
    return RET_ERROR;
}

int ret_perror(char const *name, char const *format, ...)
{
    va_list ap;
    char *str;

    if (format == NULL)
        return ret_perror(name, "%s.\n", strerror(errno));
    va_start(ap, format);
    my_vasprintf(&str, format, ap);
    va_end(ap);
    my_dprintf(STDERR_FILENO, "%s: %s", name, str);
    free(str);
    return RET_ERROR;
}
