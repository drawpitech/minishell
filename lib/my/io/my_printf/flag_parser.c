/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** flag_parser
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#include "string.h"
#include "std.h"

#include "internal.h"

static
func_t *get_func(char c)
{
    for (int i = 0; i < FORMAT_N; i++)
        if (FORMAT_FUNCS[i].format == c)
            return FORMAT_FUNCS[i].func;
    return NULL;
}

static
int get_simple_flags(printf_t *pr, printf_args_t *arg)
{
    if (pr->format[pr->index] == '#') {
        arg->flags.alternative_form = true;
        pr->index += 1;
        return get_simple_flags(pr, arg);
    }
    if (pr->format[pr->index] == ' ') {
        arg->flags.space = true;
        pr->index += 1;
        return get_simple_flags(pr, arg);
    }
    if (pr->format[pr->index] == '+') {
        arg->flags.sign = true;
        pr->index += 1;
        return get_simple_flags(pr, arg);
    }
    if (pr->format[pr->index] == 'I' || pr->format[pr->index] == '\'') {
        pr->index += 1;
        return get_simple_flags(pr, arg);
    }
    return 0;
}

static
void get_flags(printf_t *pr, printf_args_t *arg)
{
    arg->flags = (struct flags_s){ 0 };
    get_simple_flags(pr, arg);
    if (IS_NUM(pr->format[pr->index]) || pr->format[pr->index] == '-') {
        arg->flags.padding = str_to_int(pr->format + pr->index);
        arg->flags.padded = true;
        pr->index += (
            (int)my_nbr_len_base(arg->flags.padding, BASE_DEC)
            + (pr->format[pr->index] == '-' && arg->flags.padding == 0)
        );
    }
}

static
bool get_precision(printf_t *pr, printf_args_t *arg)
{
    static const int default_precision = 6;
    int tmp;

    arg->precision = default_precision;
    if (pr->format[pr->index] != '.')
        return true;
    tmp = str_to_int(pr->format + pr->index + 1);
    if (tmp <= 0 && pr->format[pr->index + 1] == '-')
        return false;
    pr->index += 1;
    arg->precision = tmp;
    pr->index += (
        (int)my_nbr_len_base(tmp, BASE_DEC)
        + (pr->format[pr->index] == '-' && tmp == 0)
    );
    return true;
}

void may_you_show_with_fmt(printf_t *pr)
{
    printf_args_t arg = { 0 };
    func_t *func = NULL;
    size_t start = pr->index;

    pr->index += 1;
    get_flags(pr, &arg);
    if (!get_precision(pr, &arg)) {
        add_in_buf(pr, "%.0");
        pr->index += 1;
        return;
    }
    func = get_func(pr->format[pr->index]);
    pr->index += 1;
    if (func != NULL) {
        func(pr, &arg);
        return;
    }
    pr->index = start;
    print_till_purcent(pr);
}
