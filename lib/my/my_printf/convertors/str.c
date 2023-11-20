/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** str
*/

#include <stdarg.h>
#include <stdlib.h>

#include "my.h"
#include "../my_printf.h"

void printf_str(printf_t *pr, printf_args_t *arg)
{
    char *str = va_arg(pr->ap, char *);

    write_flag(pr, arg, (str != NULL) ? str : "(null)");
}
