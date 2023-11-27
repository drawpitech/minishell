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

typedef int (builtin_cmd_t)(shell_t *);

int builtin_exit(shell_t *shell);
int builtin_env(shell_t *shell);

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
    { NULL, NULL },
};

#endif /* BUILTINS_H_ */
