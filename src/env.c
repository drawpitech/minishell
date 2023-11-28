/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** env
*/

#include <dirent.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "debug.h"
#include "minishell.h"
#include "my.h"

env_variable_t *my_getenv(shell_t *shell, char const *variable)
{
    if (shell == NULL || variable == NULL)
        return NULL;
    for (size_t i = 0; i < shell->env.count; i++) {
        if (shell->env.variables[i].key == NULL)
            continue;
        if (my_strcmp(shell->env.variables[i].key, variable) == 0)
            return shell->env.variables + i;
    }
    return NULL;
}
char *my_setenv(char **env, char const *variable)
{
    UNUSED char *current;

    if (env == NULL || variable == NULL)
        return NULL;
    return NULL;
}

static
int add_env_variable(shell_t *shell, char *const *env, char **ptr, size_t i)
{
    my_strcpy(*ptr, env[i]);
    shell->env.variables[i].key = *ptr;
    *ptr = my_strfind(*ptr, '=');
    if (*ptr == NULL) {
        free(shell->env.variables);
        return RET_ERROR;
    }
    **ptr = '\0';
    shell->env.variables[i].value = *ptr + 1;
    *ptr += my_strlen(*ptr + 1) + 2;
    return RET_VALID;
}

int init_env(shell_t *shell, char *const *env)
{
    char *ptr;
    size_t size = 0;
    size_t alloc_str = 0;

    if (env == NULL)
        return RET_VALID;
    while (env[size] != NULL) {
        alloc_str += my_strlen(env[size]) + 1;
        size += 1;
    }
    shell->env.variables = malloc((size + 1) * sizeof(env_variable_t)
        + (alloc_str + 1) * sizeof(char));
    if (shell->env.variables == NULL)
        return RET_ERROR;
    ptr = (char *)shell->env.variables + (size + 1) * sizeof(env_variable_t);
    shell->env.count = size;
    for (size_t i = 0; i < shell->env.count; i++)
        if (add_env_variable(shell, env, &ptr, i) == RET_ERROR)
            return RET_ERROR;
    return RET_VALID;
}

static
void append_env_var(shell_t *shell, char ***envptr, size_t i, char **pool)
{
    env_variable_t *var = shell->env.variables + i;

    if (var->key == NULL)
        return;
    **envptr = *pool;
    *envptr += 1;
    my_strapp(pool, var->key);
    my_strapp(pool, "=");
    my_strapp(pool, var->value);
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
        size += my_strlen(shell->env.variables[i].key)
            + my_strlen(shell->env.variables[i].value) + 2;
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
