/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** sprintf
*/

#include <unistd.h>

#include "io.h"
#include "math.h"
#include "string.h"

#include "../internal.h"

size_t my_vsprintf(
    char *restrict str,
    const char *restrict format,
    va_list ap)
{
    char *buf = NULL;
    size_t size = my_vasprintf(&buf, format, ap);

    if (str != NULL)
        my_strcpy(str, buf);
    return size;
}

size_t my_sprintf(
    char *restrict str,
    const char *restrict format,
    ...)
{
    va_list ap;
    size_t size = 0;

    if (format == NULL)
        return my_sprintf(str, "(null)");
    va_start(ap, format);
    size = my_vsprintf(str, format, ap);
    va_end(ap);
    return size;
}

size_t my_vsnprintf(
    char *restrict str,
    size_t size,
    const char *restrict format,
    va_list ap)
{
    char *buf = NULL;
    size_t ret = my_vasprintf(&buf, format, ap);

    if (str != NULL)
        my_strncpy(str, buf, size);
    return MIN(size, ret);
}

size_t my_snprintf(
    char *restrict str,
    size_t size,
    const char *restrict format,
    ...)
{
    va_list ap;
    size_t ret = 0;

    if (format == NULL)
        return my_snprintf(str, size, "(null)");
    va_start(ap, format);
    ret = my_vsnprintf(str, size, format, ap);
    va_end(ap);
    return ret;
}
