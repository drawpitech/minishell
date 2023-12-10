/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** write_number
*/

#include "string.h"

static
size_t print_digits(
    unsigned long long n,
    char const *base,
    size_t len,
    char **ptr)
{
    size_t size;

    if (n == 0)
        return 0;
    size = print_digits(n / len, base, len, ptr);
    **ptr = base[n % len];
    *ptr += 1;
    return size + 1;
}

size_t write_uint_base(unsigned long long nbr, char const *base, char *buf)
{
    size_t len = my_strlen(base);
    char *ptr = buf;

    if (len == 0)
        return 0;
    if (nbr == 0) {
        buf[0] = base[0];
        return 1;
    }
    return print_digits(nbr, base, len, &ptr);
}

size_t write_int_base(long long nbr, char const *base, char *buf)
{
    if (base[0] == '\0')
        return 0;
    if (nbr < 0) {
        buf[0] = '-';
        return write_uint_base(-nbr, base, buf + 1);
    }
    return write_uint_base(nbr, base, buf);
}
