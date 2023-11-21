/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** env
*/

#include <dirent.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <sys/types.h>

#include "my.h"
#include "minishell.h"

char const *my_getenv(char *const *env, char const *variable)
{
    static char arg_name[131072];

    if (env == NULL || variable == NULL)
        return NULL;
    my_strcpy(arg_name, variable);
    my_strcat(arg_name, "=");
    for (; *env != NULL; env++)
        if (*env != NULL && my_str_startswith(*env, arg_name))
            return *env + my_strlen(arg_name);
    return NULL;
}

static
bool is_file_here(char const **env_path, char const *file)
{
    static char dirpath[PATH_MAX];
    DIR *dir;
    char *tmp = my_strfind(*env_path, ':');
    size_t offset = (tmp == NULL) ? my_strlen(*env_path) : tmp - *env_path;
    struct dirent *dirent;

    my_strncpy(dirpath, *env_path, offset);
    dir = opendir(dirpath);
    while (dir != NULL) {
        dirent = readdir(dir);
        if (dirent == NULL)
            break;
        if (my_strcmp(file, dirent->d_name) != 0)
            continue;
        return true;
    }
    *env_path += offset + 1;
    if (dir != NULL)
        closedir(dir);
    return false;
}

char *get_cmd_in_path(char const *cmd, char *const *env)
{
    static char fullpath[PATH_MAX];
    char const *env_path;

    if (cmd == NULL || env == NULL)
        return NULL;
    env_path = my_getenv(env, "PATH");
    if (env_path == NULL) {
        ret_perror("mysh", "variable 'PATH' missing.");
        return NULL;
    }
    for (; *env_path;) {
        if (!is_file_here(&env_path, cmd))
            continue;
        get_fullpath(env_path, cmd, fullpath);
        return fullpath;
    }
    return NULL;
}
