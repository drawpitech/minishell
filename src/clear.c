/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** clear
*/

#include <stdlib.h>

#include "minishell.h"

void clear_prompt(prompt_t *prompt)
{
    if (prompt == NULL)
        return;
    if (prompt->line != NULL)
        free(prompt->line);
    if (prompt->tokens.tok != NULL)
        free(prompt->tokens.tok);
    *prompt = (prompt_t){ 0 };
}

void clear_shell(shell_t *shell)
{
    if (shell == NULL)
        return;
    clear_prompt(&shell->prompt);
    if (shell->env.variables != NULL)
        free(shell->env.variables);
    if (shell->env.data != NULL)
        free(shell->env.data);
    *shell = (shell_t){ 0 };
}
