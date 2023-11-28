/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** env
*/

#include "my.h"

#include "../debug.h"
#include "builtins.h"

int builtin_env(shell_t *shell, UNUSED char **argv)
{
    env_variable_t *var;
    char *ptr;

    if (shell == NULL)
        return SH_CODE_GENERAL_ERROR;
    ptr = (char *)shell->env.variables;
    for (size_t i = 0; i < shell->env.count; i++) {
        var = shell->env.variables + i;
        if (var->key == 0)
            continue;
        my_printf("%s=%s\n", ptr + var->key, ptr + var->value);
    }
    return SH_CODE_SUCCES;
}

int builtin_unsetenv(shell_t *shell, char **argv)
{
    char *key;
    env_variable_t *var;

    if (shell == NULL || argv == NULL || argv[0] == NULL || argv[1] == NULL)
        return SH_CODE_GENERAL_ERROR;
    key = argv[1];
    var = my_getenv(shell, key);
    if (var == NULL) {
        ret_perror("unsetenv", "cannot find variable `%s`\n", key);
        return SH_CODE_GENERAL_ERROR;
    }
    var->key = 0;
    DEBUG("Unset env variable `%s`", argv[1]);
    return SH_CODE_SUCCES;
}
