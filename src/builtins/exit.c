/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** exit
*/

#include "my.h"

#include "builtins.h"

int builtin_exit(shell_t *shell, UNUSED char **argv)
{
    shell->is_running = false;
    return SH_CODE_SUCCES;
}
