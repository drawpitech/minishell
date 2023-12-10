/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_sqrt
*/

#include "math.h"

int my_sqrt(int nb)
{
    int tmp;

    for (int i = 1; i <= nb; i++) {
        tmp = (int)my_pow(i, 2);
        if (tmp == 0)
            return 0;
        if (tmp == nb)
            return i;
        if (tmp > nb)
            return 0;
    }
    return 0;
}
