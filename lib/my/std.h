/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** std
*/

#ifndef LIBMY
    #define LIBMY

    #include <stdint.h>
    #include <stdlib.h>

    #define BOOL(arg) (!!(arg))
    #define CHR(n) ((n) + '0')
    #define ATTR(x) __attribute__((x))
    #define STRBOOL(check) ((check) ? "true" : "false")

    #define NOT_NULL ((void *)1)
    #define USED ATTR(used)
    #define UNUSED ATTR(unused)

enum {
    RET_VALID = 0,
    RET_ERROR = 84,
};

typedef int (compar_func_t)(void const *, void const *);

int get_color(unsigned char red, unsigned char green, unsigned char blue);

int ret_error(char const *format, ...);
int ret_perror(char const *name, char const *format, ...);

size_t my_i64_len(int64_t n);
size_t my_i64_len_base(int64_t n, const char *base);
size_t my_nbr_len_base(size_t n, const char *base);
size_t my_u64_len(uint64_t n);
size_t my_u64_len_base(uint64_t n, const char *base);

void *my_calloc(size_t nmemb, size_t size);
void *my_realloc(void *ptr, size_t size, size_t old);
void *my_reallocarray(void *ptr, size_t nmemb, size_t nmemb_old, size_t size);

void my_qsort(void *arr, size_t nmemb, size_t size, compar_func_t *compar);
void my_swap(void *left, void *right, size_t size);

#endif /* LIBMY */
