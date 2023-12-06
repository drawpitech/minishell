/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** cmd_path
*/

#include <dirent.h>

#include "../debug.h"
#include "execute.h"

#include "my.h"

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

static
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
    for (char *ptr = env_path; *ptr;) {
        fullpath = get_file_in_dir(&ptr, cmd);
        if (fullpath != NULL)
            return fullpath;
    }
    return NULL;
}

char const *get_cmd(shell_t *shell, char const *str)
{
    char *cmd;

    for (size_t i = 0; str[i]; i++)
        if (str[i] == '/')
            return str;
    cmd = get_cmd_in_path(shell, str);
    if (cmd != NULL)
        return cmd;
    ret_perror(str, "Command not found.\n");
    return NULL;
}
