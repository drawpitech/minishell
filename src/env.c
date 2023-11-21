/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** env
*/

#include <linux/limits.h>
#include <sys/types.h>

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "minishell.h"
#include "my.h"

char *my_getenv(char **env, char const *variable)
{
    size_t size = (variable != NULL) ? my_strlen(variable) + 2 : 0;
    char arg_name[size];

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
bool is_file_in_dir(char const *dir, char const *file)
{
    struct dirent *dirent = NOT_NULL;
    DIR *dirp = opendir(dir);

    DEBUG("%s -> %s", STRBOOL(dir != NULL), dir);
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

char *get_cmd_in_path(char const *cmd, char **env)
{
    char *env_path;
    char *fullpath;

    if (cmd == NULL || env == NULL)
        return NULL;
    env_path = my_getenv(env, "PATH");
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
