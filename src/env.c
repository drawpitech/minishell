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

char *my_getenv(shell_t *shell, char const *variable)
{
    if (shell == NULL || variable == NULL)
        return NULL;
    for (size_t i = 0; i < shell->env.count; i++)
        if (my_strcmp(shell->env.variables[i].key, variable) == 0)
            return shell->env.variables[i].value;
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
bool is_file_in_dir(char const *dir, char const *file)
{
    struct dirent *dirent = NOT_NULL;
    DIR *dirp = opendir(dir);

    if (dirp == NULL)
        return false;
    while (dirent != NULL) {
        dirent = readdir(dirp);
        if (dirent == NULL)
            break;
        if (my_strcmp(file, dirent->d_name) != 0)
            continue;
        DEBUG("dir: %s", dir);
        closedir(dirp);
        return true;
    }
    closedir(dirp);
    return false;
}

static
char *get_file_in_dir(char **env_path, char const *file)
{
    static char dirpath[PATH_MAX];
    char *tmp = my_strfind(*env_path, ':');
    size_t offset = (tmp == NULL)
        ? my_strlen(*env_path)
        : (size_t)(tmp - *env_path);

    my_strncpy(dirpath, *env_path, offset);
    dirpath[offset] = '\0';
    *env_path += offset + (tmp != NULL);
    return (is_file_in_dir(dirpath, file))
        ? get_fullpath(dirpath, file, dirpath)
        : NULL;
}

char *get_cmd_in_path(shell_t *shell, char const *cmd)
{
    char *env_path;
    char *fullpath;

    if (cmd == NULL)
        return NULL;
    env_path = my_getenv(shell, "PATH");
    if (env_path == NULL) {
        ret_perror("mysh", "variable 'PATH' missing.");
        return NULL;
    }
    for (; *env_path;) {
        fullpath = get_file_in_dir(&env_path, cmd);
        if (fullpath != NULL)
            return fullpath;
    }
    return NULL;
}

int init_env(shell_t *shell, char *const *env)
{
    char *pool;
    size_t size = 0;
    size_t alloc_str = 0;
    char *tmp;

    if (env == NULL)
        return RET_VALID;
    while (env[size] != NULL) {
        alloc_str += my_strlen(env[size]) + 1;
        size += 1;
    }
    pool = malloc((alloc_str + 1) * sizeof(char));
    if (pool == NULL)
        return RET_ERROR;
    shell->env.variables =  malloc((size + 1) * sizeof(env_variable_t));
    if (shell->env.variables == NULL) {
        free(pool);
        return RET_ERROR;
    }
    pool[alloc_str] = '\0';
    shell->env.pool = pool;
    shell->env.count = size;
    for (size_t i = 0; i < shell->env.count; i++) {
        my_strcpy(pool, env[i]);
        tmp = my_strfind(pool, '=');
        if (tmp == NULL) {
            free(shell->env.pool);
            free(shell->env.variables);
            return RET_ERROR;
        }
        *tmp = '\0';
        shell->env.variables[i].key = pool;
        shell->env.variables[i].value = tmp + 1;
        pool += my_strlen(env[i]) + 1;
    }
    return RET_VALID;
}

static
void append_env_var(shell_t *shell, char **envp, size_t i, char **pool)
{
    env_variable_t *var = shell->env.variables + i;

    envp[i] = *pool;
    my_strapp(pool, var->key);
    my_strapp(pool, "=");
    my_strapp(pool, var->value);
    *pool += 1;
}

char **get_envp(shell_t *shell)
{
    size_t size = 0;
    char **envp;
    char *pool;

    if (shell == NULL)
        return NULL;
    for (size_t i = 0; i < shell->env.count; i++)
        size += my_strlen(shell->env.variables[i].key)
            + my_strlen(shell->env.variables[i].value) + 2;
    envp = malloc((shell->env.count + 1) * sizeof(char *)
        + (size + 1) * sizeof(char));
    if (envp == NULL)
        return NULL;
    pool = (char *)envp + (shell->env.count + 1) * sizeof(char *);
    pool[size] = '\0';
    for (size_t i = 0; i < shell->env.count; i++)
        append_env_var(shell, envp, i, &pool);
    envp[shell->env.count] = NULL;
    return envp;
}
