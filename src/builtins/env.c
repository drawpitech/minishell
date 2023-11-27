/*
** EPITECH PROJECT, 2023
** bob
** File description:
** bob
*/

#include "builtins.h"
#include "my.h"

int builtin_env(shell_t *shell, UNUSED char **argv)
{
    env_variable_t *var;

    if (shell == NULL)
        return SH_CODE_GENERAL_ERROR;
    for (size_t i = 0; i < shell->env.count; i++) {
        var = shell->env.variables + i;
        my_printf("%s=%s\n", var->key, var->value);
    }
    return SH_CODE_SUCCES;
}
