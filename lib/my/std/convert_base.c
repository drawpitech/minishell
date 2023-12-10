/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** convert_base
*/

#include "string.h"

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    return my_nbr_to_base(str_to_int_base(nbr, base_from), base_to);
}
