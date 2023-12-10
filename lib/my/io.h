/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** io
*/

#ifndef MY_IO_H_
    #define MY_IO_H_

    #include <stdarg.h>
    #include <stdlib.h>

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

size_t my_putnchar(char c, size_t n);
size_t my_putnstr(char const *str, size_t n);
size_t my_putstr(const char *str);
void my_putchar(char c);

#endif /* MY_IO_H_ */
