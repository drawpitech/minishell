/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my
*/

#ifndef LIBMY
    #define LIBMY

    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>

    #define IS_LOWERCASE(c) ((c) >= 'a' && (c) <= 'z')
    #define IS_UPPERCASE(c) ((c) >= 'A' && (c) <= 'Z')
    #define IS_ALPHA(c) (IS_LOWERCASE(c) || IS_UPPERCASE(c))
    #define IS_NUM(c) ((c) >= '0' && (c) <= '9')
    #define IS_ALPHANUM(c) (IS_NUM(c) || IS_ALPHA(c))
    #define IS_PRINTABLE(c) ((c) >= ' ' && (c) <= '~')

    #define CH_LOW(c) (IS_UPPERCASE(c) ? ((c) + 32) : (c))
    #define CH_UPP(c) (IS_LOWERCASE(c) ? ((c) - 32) : (c))

    #define MIN(x, y) (((x) < (y)) ? (x) : (y))
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))
    #define ABS(n) (((n) > 0) ? (n) : -(n))

    #define BASE_BIN "01"
    #define BASE_OCT "01234567"
    #define BASE_DEC "0123456789"
    #define BASE_HEX "0123456789abcdef"
    #define BASE_HEX_MIN "0123456789abcdef"
    #define BASE_HEX_MAJ "0123456789ABCDEF"

    #define BOOL(arg) (!!(arg))
    #define CHR(n) ((n) + '0')
    #define ATTR(x) __attribute__((x))

enum {
    RET_VALID = 0,
    RET_ERROR = 84,
};

typedef int (compar_func_t)(void const *, void const *);

bool my_str_isalpha(char const *str);
bool my_str_islower(char const *str);
bool my_str_isnum(char const *str);
bool my_str_isprintable(char const *str);
bool my_str_isupper(char const *str);
bool my_str_startswith(const char *big, const char *little);
char *convert_base(char const *, char const *, char const *);
char *get_fullpath(char const *directory, char const *filename, char *result);
char *my_nbr_to_base(int nbr, char const *base);
char *my_revstr(char *src);
char *my_str_join(size_t argc, char *const *argv, char const *separator);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strfind(char *str, char c);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, size_t nb);
char *my_strncpy(char *dest, char const *src, size_t n);
char *my_strndup(char const *src, size_t n);
char *my_strpbrk(char *str, char const *chars);
char *my_strupcase(char *str);
char const *my_strstr(char const *str, char const *to_find);
int count_island(char **world);
int get_color(unsigned char red, unsigned char green, unsigned char blue);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_show_word_array(char *const *tab);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, size_t n);
int ret_error(char const *format, ...);
int ret_perror(char const *name, char const *format, ...);
int str_to_int(char const *str);
int str_to_int_base(char const *str, char const *base);
size_t my_i64_len(int64_t n);
size_t my_i64_len_base(int64_t n, const char *base);
size_t my_nbr_len_base(size_t n, const char *base);
size_t my_putnchar(char c, size_t n);
size_t my_putnstr(char const *str, size_t n);
size_t my_putstr(const char *str);
size_t my_strlen(char const *str);
size_t my_u64_len(uint64_t n);
size_t my_u64_len_base(uint64_t n, const char *base);
size_t write_int_base(long long nbr, char const *base, char *buf);
size_t write_uint_base(unsigned long long nbr, char const *base, char *buf);
void *my_calloc(size_t nmemb, size_t size);
void *my_memcpy(void *restrict dest, const void *restrict src, size_t n);
void *my_memset(void *s, int c, size_t n);
void *my_realloc(void *ptr, size_t size, size_t old);
void *my_reallocarray(void *ptr, size_t nmemb, size_t nmemb_old, size_t size);
void *reverse_arr(uint32_t size, void *arr, size_t memsize);
void my_putchar(char c);
void my_qsort(void *arr, size_t nmemb, size_t size, compar_func_t *compar);
void my_swap(void *left, void *right, size_t size);

uint32_t my_pow(uint32_t x, uint32_t y);
int my_sqrt(int nb);
bool my_is_prime(int nb);

/*
 * Produce output according to a format.
 * Prints result in stdout
 **/
size_t my_printf(
    const char *restrict format,
    ...);

/*
 * Produce output according to a format.
 * Prints result in stdout
 **/
size_t my_vprintf(
    const char *restrict format,
    va_list ap);

/*
 * Produce output according to a format.
 * Write result in fd.
 **/
size_t my_dprintf(
    int fd,
    const char *restrict format,
    ...);

/*
 * Produce output according to a format.
 * Write result in fd.
 **/
size_t my_vdprintf(
    int fd,
    const char *restrict format,
    va_list ap);

/*
 * Produce output according to a format.
 * Copy result in str.
 **/
size_t my_sprintf(
    char *restrict str,
    const char *restrict format,
    ...);

/*
 * Produce output according to a format.
 * Copy result in str.
 **/
size_t my_vsprintf(
    char *restrict str,
    const char *restrict format,
    va_list ap);

/*
 * Produce output according to a format.
 * Copy first n characters of the result in str.
 **/
size_t my_snprintf(
    char *restrict str,
    size_t size,
    const char *restrict format,
    ...);

/*
 * Produce output according to a format.
 * Copy first n characters of the result in str.
 **/
size_t my_vsnprintf(
    char *restrict str,
    size_t size,
    const char *restrict format,
    va_list ap);

/*
 * Produce output according to a format.
 * Allocate a string and copy the result in it.
 **/
size_t my_asprintf(
    char **strp,
    const char *restrict format,
    ...);

/*
 * Produce output according to a format.
 * Allocate a string and copy the result in it.
 **/
size_t my_vasprintf(
    char **strp,
    const char *restrict format,
    va_list ap);

#endif /* LIBMY */
