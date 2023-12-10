/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** internal
*/

#ifndef MY_PRINTF_H_
    #define MY_PRINTF_H_

    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>

    #define FORMAT_N 17

typedef struct {
    struct flags_s {
        bool alternative_form;
        int padding;
        bool padded;
        bool space;
        bool sign;
    } flags;
    int precision;
} printf_args_t;

typedef struct {
    char *str;
    size_t size;
    size_t alloc_size;
} buffer_t;

typedef struct {
    char const *restrict format;
    va_list ap;
    buffer_t buf;
    size_t index;
} printf_t;

typedef void (func_t)(printf_t *, printf_args_t *);

typedef struct {
    char format;
    func_t *func;
} format_t;

void add_in_buf(printf_t *pr, char const *buf);
void print_till_purcent(printf_t *pr);
void may_you_show_with_fmt(printf_t *pr);
void write_flag(printf_t *pr, printf_args_t const *arg, char const *buf);
void printf_int(printf_t *pr, printf_args_t *arg);
void printf_char(printf_t *pr, printf_args_t *arg);
void printf_purcent(printf_t *pr, printf_args_t *arg);
void printf_str(printf_t *pr, printf_args_t *arg);
void printf_octal(printf_t *pr, printf_args_t *arg);
void printf_decimal(printf_t *pr, printf_args_t *arg);
void printf_hexadecimal(printf_t *pr, printf_args_t *arg);
void printf_hexadecimal2(printf_t *pr, printf_args_t *arg);
void printf_pointer(printf_t *pr, printf_args_t *arg);
void printf_float(printf_t *pr, printf_args_t *arg);
void printf_len(printf_t *pr, printf_args_t *arg);

static
const format_t FORMAT_FUNCS[FORMAT_N] = {
    {'d', &printf_int},
    {'i', &printf_int},
    {'%', &printf_purcent},
    {'c', &printf_char},
    {'s', &printf_str},
    {'o', &printf_octal},
    {'u', &printf_decimal},
    {'x', &printf_hexadecimal},
    {'X', &printf_hexadecimal2},
    {'p', &printf_pointer},
    {'f', &printf_float},
    {'F', &printf_float},
    {'n', &printf_len},
};

#endif /* MY_PRINTF_H_ */
