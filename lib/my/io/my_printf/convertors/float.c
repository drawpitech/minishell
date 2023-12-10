/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** float
*/

#include "string.h"

#include "../internal.h"

static
int get_leftover(double n, size_t len, int precision)
{
    n -= (double)(long)n;
    n *= (double)len;
    if (precision == 0)
        return (n >= (double)len / 2);
    return (get_leftover(n, len, precision - 1) + n >= (double)len);
}

static
size_t get_after_point(double n, const char *base, int precision, char **buf)
{
    size_t len = my_strlen(base);

    for (int i = 0; i < precision; i++) {
        n -= (double)(long)n;
        n *= (double)len;
        n += get_leftover(n, len, precision);
        **buf = base[(int)n % len];
        *buf += 1;
    }
    return precision;
}

static
size_t write_double_base(double n, const char *base, int precision, char *buf)
{
    size_t len = my_strlen(base);
    size_t size = write_uint_base(
        (long)n + get_leftover(n, len, precision),
        base,
        buf);
    char *ptr = buf + size;

    if (precision > 0) {
        my_strcpy(ptr, ".");
        ptr += 1;
        size += get_after_point(n, base, precision, &ptr);
    }
    return size;
}

void printf_float(printf_t *pr, printf_args_t *arg)
{
    size_t size = 0;
    double nbr = va_arg(pr->ap, double);
    char buf[64 + arg->precision];

    my_memset(buf, 0, 64 + arg->precision);
    if (arg->flags.sign) {
        buf[0] = (nbr >= 0) ? '+' : '-';
        size += 1;
    } else if (arg->flags.space && nbr >= 0) {
        buf[0] = ' ';
        size += 1;
    }
    write_double_base(nbr, BASE_DEC, arg->precision, buf + size);
    write_flag(pr, arg, buf);
}
