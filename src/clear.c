/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** clear
*/

#include "minishell.h"
#include <stdlib.h>

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
    *shell = (shell_t){ 0 };
}
