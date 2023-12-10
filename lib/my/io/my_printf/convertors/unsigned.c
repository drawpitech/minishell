/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** unsigned
*/

#include "string.h"

#include "../internal.h"

static
char *printf_unsigned(
    printf_t *pr,
    char const *base,
    char const *alter,
    char *buf)
{
    size_t size = 0;
    unsigned int nbr = va_arg(pr->ap, unsigned int);

    if (alter != NULL && nbr != 0) {
        my_strcpy(buf, alter);
        size += my_strlen(alter);
    }
    write_uint_base(nbr, base, buf + size);
    return buf;
}

void printf_octal(printf_t *pr, printf_args_t *arg)
{
    static char buffer[12] = {0};

    my_memset(buffer, 0, 12);
    write_flag(pr, arg, printf_unsigned(pr, BASE_OCT, NULL, buffer));
}

void printf_decimal(printf_t *pr, printf_args_t *arg)
{
    static char buffer[12] = {0};

    my_memset(buffer, 0, 12);
    write_flag(pr, arg, printf_unsigned(pr, BASE_DEC, NULL, buffer));
}

void printf_hexadecimal(printf_t *pr, printf_args_t *arg)
{
    bool alter = (arg->flags.alternative_form);
    static char buffer[12] = {0};

    my_memset(buffer, 0, 12);
    write_flag(pr, arg,
        printf_unsigned(pr, BASE_HEX_MIN, (alter) ? "0x" : NULL, buffer));
}

void printf_hexadecimal2(printf_t *pr, printf_args_t *arg)
{
    bool alter = (arg->flags.alternative_form);
    static char buffer[12] = {0};

    my_memset(buffer, 0, 12);
    write_flag(pr, arg,
        printf_unsigned(pr, BASE_HEX_MAJ, (alter) ? "0X" : NULL, buffer));
}
