/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** builtins
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_

    #include <stdlib.h>

    #include "../minishell.h"

typedef int (builtin_cmd_t)(shell_t *, char **);

int builtin_exit(shell_t *shell, char **argv);
int builtin_env(shell_t *shell, char **argv);
int builtin_unsetenv(shell_t *shell, char **argv);
int builtin_getenv(shell_t *shell, char **argv);
int builtin_setenv(shell_t *shell, char **argv);
int builtin_cd(shell_t *shell, char **argv);
int builtin_pwd(shell_t *shell, char **argv);

/*
 * Get the builtin corresponding to the string cmd.
 **/
builtin_cmd_t *get_builtin(char const *cmd);

static const struct {
    char *name;
    builtin_cmd_t *func;
} BUILTINS[] = {
    { "exit", &builtin_exit },
    { "env", &builtin_env },
    { "unsetenv", &builtin_unsetenv },
    { "getenv", &builtin_getenv },
    { "setenv", &builtin_setenv },
    { "cd", &builtin_cd },
    { "pwd", &builtin_pwd },
    { NULL, NULL },
};

#endif /* BUILTINS_H_ */
