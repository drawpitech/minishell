/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** cd
*/

#include <unistd.h>

#include "my.h"

#include "../debug.h"
#include "builtins.h"

static
char const *cd_get_fullpath(shell_t *shell, char const *direction, char *buf)
{
    char *home = my_getenv(shell, "HOME");

    if (direction == NULL) {
        if (home == NULL) {
            ret_perror("cd", "HOME not set");
            return NULL;
        }
        return home;
    }
    if (direction[0] == '~') {
        if (home == NULL) {
            ret_perror("cd", "HOME not set");
            return NULL;
        }
        get_fullpath(home, direction + 2, buf);
        return buf;
    }
    get_fullpath(getcwd(buf, PATH_MAX), direction, buf);
    return buf;
}

int builtin_cd(shell_t *shell, char **argv)
{
    int ret;
    static char buf[PATH_MAX];
    char const *path;

    if (shell == NULL || argv == NULL)
        return SH_CODE_GENERAL_ERROR;
    path = cd_get_fullpath(shell, argv[1], buf);
    if (path == NULL)
        return SH_CODE_GENERAL_ERROR;
    DEBUG("cd to `%s`", path);
    ret = chdir(path);
    if (ret == -1)
        return ret_perror("cd", NULL);
    my_setenv(shell, "PWD", getcwd(buf, PATH_MAX));
    return SH_CODE_SUCCES;
}

int builtin_pwd(shell_t *shell, char **argv)
{
    static char buf[PATH_MAX];

    if (shell == NULL || argv == NULL)
        return SH_CODE_GENERAL_ERROR;
    my_printf("%s\n", getcwd(buf, PATH_MAX));
    return SH_CODE_SUCCES;
}
