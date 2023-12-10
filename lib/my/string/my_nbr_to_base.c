/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_nbr_to_base
*/

#include "std.h"
#include "string.h"

static
void set_nbr(int n, char const *base, int len, char *res)
{
    if (n == 0)
        return;
    set_nbr(n / len, base, len, res - 1);
    *res = base[-(n % len)];
}

static
int len_alloc(int n, int base_len)
{
    int res = 0;

    while (n != 0) {
        n /= base_len;
        res++;
    }
    return res;
}

static
char *zero_char(char const *base)
{
    char *res = malloc(2 * sizeof(char));

    res[0] = base[0];
    res[1] = '\0';
    return res;
}

char *my_nbr_to_base(int nbr, char const *base)
{
    size_t len = my_strlen(base);
    size_t len_res = 0;
    int is_neg = (nbr < 0);
    char *res;

    if (len == 0)
        return NULL;
    if (nbr == 0)
        return zero_char(base);
    len_res = len_alloc(nbr, (int)len);
    if (is_neg)
        len_res++;
    else
        nbr = -nbr;
    res = malloc((len_res + 1) * sizeof(char));
    if (is_neg)
        res[0] = '-';
    set_nbr(nbr, base, (int)len, res + len_res - 1);
    res[len_res] = '\0';
    return res;
}
