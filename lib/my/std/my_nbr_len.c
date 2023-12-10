/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_nbr_len
*/

#include "std.h"
#include "string.h"

size_t my_i64_len_base(int64_t n, const char *base)
{
    size_t i = (n <= 0);
    int64_t len = (int64_t)my_strlen(base);

    for (; n; n /= len)
        i++;
    return i;
}

size_t my_i64_len(int64_t n)
{
    return my_i64_len_base(n, BASE_DEC);
}

size_t my_u64_len_base(uint64_t n, const char *base)
{
    return (n == 0) ? 1 : my_i64_len_base((int64_t)n, base);
}

size_t my_u64_len(uint64_t n)
{
    return my_u64_len_base(n, BASE_DEC);
}

size_t my_nbr_len_base(size_t n, const char *base)
{
    return my_i64_len_base((int)n, base);
}
