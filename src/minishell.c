/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** minishell
*/

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "my.h"

#include "minishell.h"

static
int get_prompt(shell_t *shell)
{
    static size_t offset = 0;
    prompt_t *prompt;

    shell->prompt = (prompt_t){ 0 };
    prompt = &shell->prompt;
    my_printf("$> ");
    prompt->size = getline(&prompt->line, &offset, stdin);
    if (prompt->size == (size_t)-1) {
        shell->is_running = false;
        return RET_ERROR;
    }
    return RET_VALID;
}

static
void shell_prompt(shell_t *shell)
{
    if (get_prompt(shell) == RET_ERROR)
        return;
}

int minishell(int argc, char *const *argv, char *const *env)
{
    shell_t shell = { 0 };

    shell.is_running = true;
    shell.env = env;
    while (shell.is_running) {
        shell_prompt(&shell);
        clear_prompt(&shell.prompt);
    }
    clear_shell(&shell);
    return RET_VALID;
}
