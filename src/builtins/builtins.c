/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** builtins
*/

#include "my/string.h"

#include "../minishell.h"
#include "builtins.h"

builtin_cmd_t *get_builtin(char const *cmd)
{
    for (size_t i = 0; BUILTINS[i].func != NULL; i++)
        if (my_strcmp(BUILTINS[i].name, cmd) == 0)
            return BUILTINS[i].func;
    return NULL;
}
