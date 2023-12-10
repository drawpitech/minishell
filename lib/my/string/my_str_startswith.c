/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_str_startswith
*/

#include "string.h"

bool my_str_startswith(const char *big, const char *little)
{
    return (
        big != NULL && little != NULL
        && !my_strncmp(big, little, my_strlen(little))
    );
}
