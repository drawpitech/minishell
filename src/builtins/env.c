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
    ptr = shell->env.ptr;
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
    int ret;

    if (shell == NULL || argv == NULL || argv[0] == NULL || argv[1] == NULL)
        return SH_CODE_GENERAL_ERROR;
    key = argv[1];
    ret = my_unsetenv(shell, key);
    if (ret == RET_ERROR) {
        ret_perror("unsetenv", "cannot find variable `%s`\n", key);
        return SH_CODE_GENERAL_ERROR;
    }
    DEBUG("Unset env variable `%s`", key);
    return SH_CODE_SUCCES;
}

int builtin_getenv(shell_t *shell, char **argv)
{
    char *key;
    char *val;

    if (shell == NULL || argv == NULL || argv[0] == NULL || argv[1] == NULL)
        return SH_CODE_GENERAL_ERROR;
    key = argv[1];
    val = my_getenv(shell, key);
    if (val == NULL) {
        ret_perror("getenv", "cannot find variable `%s`\n", key);
        return SH_CODE_GENERAL_ERROR;
    }
    DEBUG("Get env variable `%s`", key);
    my_printf("%s\n", val);
    return SH_CODE_SUCCES;
}
