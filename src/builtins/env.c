/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bob
*/

#include "builtins.h"
#include "my.h"

int builtin_env(shell_t *shell)
{
    char **ptr;

    if (shell == NULL || shell->env == NULL)
        return SH_CODE_GENERAL_ERROR;
    ptr = shell->env;
    for (; *ptr != NULL; ptr++)
        my_printf("%s\n", *ptr);
    return SH_CODE_SUCCES;
}
