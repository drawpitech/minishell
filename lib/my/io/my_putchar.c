/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_putchar
*/

#include <unistd.h>

#include "io.h"

void my_putchar(char c)
{
    write(STDOUT_FILENO, &c, 1);
}

size_t my_putnchar(char c, size_t n)
{
    char buf[n];

    for (size_t i = 0; i < n; i++)
        buf[i] = c;
    return my_putnstr(buf, n);
}
