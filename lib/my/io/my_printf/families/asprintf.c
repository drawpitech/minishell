/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** asprintf
*/

#include "io.h"

#include "../internal.h"

size_t my_vasprintf(
    char **strp,
    const char *restrict format,
    va_list ap)
{
    printf_t pr = { 0 };

    pr.format = format;
    va_copy(pr.ap, ap);
    if (format == NULL) {
        va_end(pr.ap);
        return my_asprintf(strp, "(null)");
    }
    while (pr.format[pr.index]) {
        if (pr.format[pr.index] != '%') {
            print_till_purcent(&pr);
            continue;
        }
        may_you_show_with_fmt(&pr);
    }
    if (strp != NULL)
        *strp = pr.buf.str;
    va_end(pr.ap);
    return pr.buf.size;
}

size_t my_asprintf(
    char **strp,
    const char *restrict format,
    ...)
{
    va_list ap;
    size_t size = 0;

    if (format == NULL)
        return my_asprintf(strp, "(null)");
    va_start(ap, format);
    size = my_vasprintf(strp, format, ap);
    va_end(ap);
    return size;
}
