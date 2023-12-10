/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_putstr
*/

#include <unistd.h>

#include "io.h"
#include "string.h"

size_t my_putstr(char const *str)
{
    if (str == NULL)
        return my_putstr("(null)");
    return write(STDOUT_FILENO, str, my_strlen(str));
}

size_t my_putnstr(char const *str, size_t n)
{
    if (str == NULL)
        return my_putstr("(null)");
    return write(STDOUT_FILENO, str, n);
}
