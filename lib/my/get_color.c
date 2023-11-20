/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** get_color
*/

#include <stddef.h>
#include <stdlib.h>

#include "my.h"

int get_color(unsigned char red, unsigned char green, unsigned char blue)
{
    return (red << 16) + (green << 8) + blue;
}
