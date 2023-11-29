/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** env
*/

#include <dirent.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "debug.h"
#include "minishell.h"
#include "my.h"

env_variable_t *my_getenv_var(shell_t *shell, char const *variable)
{
    char *ptr;

    if (shell == NULL || variable == NULL)
        return NULL;
    ptr = shell->env.ptr;
    for (size_t i = 0; i < shell->env.count; i++) {
        if (shell->env.variables[i].key == (size_t)-1)
            continue;
        if (my_strcmp(ptr + shell->env.variables[i].key, variable) == 0)
            return shell->env.variables + i;
    }
    return NULL;
}

char *my_getenv(shell_t *shell, char const *variable)
{
    env_variable_t *var;

    if (shell == NULL || variable == NULL)
        return NULL;
    var = my_getenv_var(shell, variable);
    if (var == NULL)
        return NULL;
    return shell->env.ptr + var->value;
}

int my_unsetenv(shell_t *shell, char const *variable)
{
    env_variable_t *var;

    if (shell == NULL || variable == NULL)
        return RET_ERROR;
    var = my_getenv_var(shell, variable);
    if (var == NULL)
        return RET_ERROR;
    var->key = (size_t)-1;
    return RET_VALID;
}

static
int add_env_variable(shell_t *shell, char *const *env, size_t *offset, size_t i)
{
    char *ptr;

    my_strcpy(shell->env.ptr + *offset, env[i]);
    shell->env.variables[i].key = *offset;
    ptr = my_strfind(shell->env.ptr + *offset, '=');
    if (ptr == NULL)
        return RET_ERROR;
    *ptr = '\0';
    *offset = ptr - shell->env.ptr;
    shell->env.variables[i].value = *offset + 1;
    *offset += my_strlen(shell->env.ptr + *offset + 1) + 2;
    return RET_VALID;
}

int init_env(shell_t *shell, char *const *env)
{
    size_t offset = 0;
    size_t size = 0;
    size_t alloc_str = 0;

    if (env == NULL)
        return RET_VALID;
    for (size = 0; env[size] != NULL; size++)
        alloc_str += my_strlen(env[size]) + 1;
    shell->env.allocated = (size + 1) * sizeof(env_variable_t)
        + (alloc_str + 1) * sizeof(char);
    shell->env.variables = malloc(shell->env.allocated);
    if (shell->env.variables == NULL)
        return RET_ERROR;
    offset = 0;
    shell->env.ptr = (char *)shell->env.variables + (size + 1) * sizeof(env_variable_t);
    shell->env.count = size;
    for (size_t i = 0; i < shell->env.count; i++)
        if (add_env_variable(shell, env, &offset, i) == RET_ERROR)
            return RET_ERROR;
    return RET_VALID;
}

static
void append_env_var(shell_t *shell, char ***envptr, size_t i, char **pool)
{
    env_variable_t *var = shell->env.variables + i;

    if (var->key == (size_t)-1)
        return;
    **envptr = *pool;
    *envptr += 1;
    my_strapp(pool, shell->env.ptr + var->key);
    my_strapp(pool, "=");
    my_strapp(pool, shell->env.ptr + var->value);
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
        size += my_strlen(shell->env.ptr + shell->env.variables[i].key)
            + my_strlen(shell->env.ptr + shell->env.variables[i].value) + 2;
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
