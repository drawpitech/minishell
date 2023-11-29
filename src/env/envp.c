/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** envp
*/

#include <stddef.h>

#include "my.h"

#include "../minishell.h"

static
void append_env_var(shell_t *shell, char ***envptr, size_t i, char **pool)
{
    env_variable_t *var = shell->env.variables + i;

    if (var->key == (size_t)-1)
        return;
    **envptr = *pool;
    *envptr += 1;
    my_strapp(pool, shell->env.data + var->key);
    my_strapp(pool, "=");
    my_strapp(pool, shell->env.data + var->value);
    *pool += 1;
}

char **get_envp(shell_t *shell)
{
    size_t size = 0;
    char **envp;
    char **envptr;
    char *pool;

    if (shell == NULL)
        return NULL;
    for (size_t i = 0; i < shell->env.count; i++)
        size += my_strlen(shell->env.data + shell->env.variables[i].key)
            + my_strlen(shell->env.data + shell->env.variables[i].value) + 2;
    envp = malloc((shell->env.count + 1) * sizeof(char *)
        + (size + 1) * sizeof(char));
    envptr = envp;
    if (envp == NULL)
        return NULL;
    pool = (char *)envp + (shell->env.count + 1) * sizeof(char *);
    for (size_t i = 0; i < shell->env.count; i++)
        append_env_var(shell, &envptr, i, &pool);
    *envptr = NULL;
    return envp;
}
