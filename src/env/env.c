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

#include "../debug.h"
#include "../minishell.h"
#include "my.h"

env_variable_t *my_getenv_var(shell_t *shell, char const *variable)
{
    char *ptr;

    if (shell == NULL || variable == NULL)
        return NULL;
    ptr = shell->env.data;
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
    return shell->env.data + var->value;
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

int my_setenv(shell_t *shell, char const *key, char const *data)
{
    size_t new_size;
    char *ptr;
    env_variable_t *var;

    if (shell == NULL || key == NULL || data == NULL)
        return RET_ERROR;
    my_unsetenv(shell, key);
    new_size = shell->env.alloc_data + my_strlen(key) + my_strlen(data) + 2;
    shell->env.variables = my_reallocarray(shell->env.variables, shell->env.count + 1, shell->env.count, sizeof(env_variable_t));
    shell->env.data = my_reallocarray(shell->env.data, new_size, shell->env.alloc_data, sizeof(char));
    ptr = shell->env.data + shell->env.alloc_data;
    var = shell->env.variables + shell->env.count;
    var->key = ptr - (char *)shell->env.data;
    my_strapp(&ptr, key);
    ptr += 1;
    var->value = ptr - (char *)shell->env.data;
    my_strapp(&ptr, data);
    shell->env.alloc_data = new_size;
    shell->env.count += 1;
    return RET_VALID;
}

static
int add_env_variable(shell_t *shell, char *const *env, size_t *offset, size_t i)
{
    char *ptr;

    my_strcpy(shell->env.data + *offset, env[i]);
    shell->env.variables[i].key = *offset;
    ptr = my_strfind(shell->env.data + *offset, '=');
    if (ptr == NULL)
        return RET_ERROR;
    *ptr = '\0';
    *offset = ptr - shell->env.data;
    shell->env.variables[i].value = *offset + 1;
    *offset += my_strlen(shell->env.data + *offset + 1) + 2;
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
    shell->env.variables = malloc((size + 1) * sizeof(env_variable_t));
    shell->env.data = malloc((alloc_str + 1) * sizeof(char));
    if (shell->env.variables == NULL || shell->env.data == NULL)
        return RET_ERROR;
    shell->env.count = size;
    shell->env.alloc_data = alloc_str + 1;
    offset = 0;
    for (size_t i = 0; i < shell->env.count; i++)
        if (add_env_variable(shell, env, &offset, i) == RET_ERROR)
            return RET_ERROR;
    return RET_VALID;
}
