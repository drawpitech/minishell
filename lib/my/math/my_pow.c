/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_pow
*/

#include "math.h"

uint32_t my_pow(uint32_t x, uint32_t y)
{
    uint32_t res = 1;

    for (uint32_t i = 0; i < y; i++)
        res *= x;
    return res;
}
