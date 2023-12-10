/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_showmem
*/

#include "io.h"
#include "string.h"

static
int my_min(int a, int b)
{
    return (a < b) ? a : b;
}

static
void hexapadding(int nbr, int pad)
{
    int n = 0;

    for (int i = nbr; i != 0; i /= 16)
        n++;
    for (int i = 0; i != pad - n; i++)
        my_putchar('0');
    if (nbr != 0)
        my_printf("%x", nbr);
}

static
void putstuff(char const *str, int size)
{
    unsigned char c;

    for (int i = 0; i < size; i++) {
        c = str[i];
        if (c < 16)
            my_putchar('0');
        my_printf("%x", c);
        if (i % 2)
            my_putchar(' ');
    }
}

static
void showmem_line(char const *str, int index, int size)
{
    hexapadding(index, 8);
    my_putchar(':');
    my_putchar(' ');
    putstuff(str + index, size);
    for (int i = size; i < 16; i++) {
        my_putchar(' ');
        my_putchar(' ');
        if (i % 2)
            my_putchar(' ');
    }
    for (int i = 0; i < size; i++) {
        if (!IS_PRINTABLE(str[i + index]))
            my_putchar('.');
        else
            my_putchar(str[i + index]);
    }
    my_putchar('\n');
}

int my_showmem(char const *str, int size)
{
    if (!str)
        return 0;
    for (int i = 0; i < size / 16 + (size % 16 != 0); i += 1)
        showmem_line(str, (i * 16), my_min(16, size - (i * 16)));
    return 0;
}
