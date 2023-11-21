/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** exit
*/

#include "../minishell.h"
#include "builtins.h"

int builtin_exit(shell_t *shell)
{
    shell->is_running = false;
    return SH_CODE_SUCCES;
}
