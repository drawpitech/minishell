/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** cd
*/

#include <unistd.h>

#include "my/io.h"
#include "my/debug.h"
#include "my/std.h"
#include "my/string.h"

#include "builtins.h"

static
char const *get_env_var(shell_t *shell, char const *var)
{
    char const *res = my_getenv(shell, var);

    if (res == NULL)
        ret_perror("cd", "%s not set", var);
    return res;
}

static
char const *cd_get_fullpath(shell_t *shell, char const *direction, char *buf)
{
    char const *tmp;

    if (direction == NULL)
        return get_env_var(shell, "HOME");
    if (direction[0] == '~') {
        tmp = get_env_var(shell, "HOME");
        if (tmp == NULL)
            return NULL;
        get_fullpath(tmp, direction + 2, buf);
        return buf;
    }
    if (direction[0] == '-')
        return get_env_var(shell, "OLDPWD");
    get_fullpath(getcwd(buf, PATH_MAX), direction, buf);
    return buf;
}

int builtin_cd(shell_t *shell, char **argv)
{
    int ret;
    static char buf[PATH_MAX];
    char const *path;
    char current[PATH_MAX];

    if (shell == NULL || argv == NULL)
        return SH_CODE_GENERAL_ERROR;
    getcwd(current, PATH_MAX);
    path = cd_get_fullpath(shell, argv[1], buf);
    if (path == NULL)
        return SH_CODE_GENERAL_ERROR;
    DEBUG("cd to `%s`", path);
    ret = chdir(path);
    if (ret == -1)
        return ret_perror(argv[1], NULL);
    my_setenv(shell, "OLDPWD", current);
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
