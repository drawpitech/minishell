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

#include "debug.h"
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
void tokenize(shell_t *shell)
{
    prompt_t *prompt = &shell->prompt;
    token_t tok = { 0 };
    char *ptr = prompt->line;

    while (parser_next_token(&ptr, &tok) != NULL) {
        DEBUG("token: [%s]", tok.ptr);
        prompt->tokens.tok = my_reallocarray(
            prompt->tokens.tok, prompt->tokens.nbr + 1,
            prompt->tokens.nbr, sizeof(*prompt->tokens.tok)
        );
        my_memcpy(prompt->tokens.tok + prompt->tokens.nbr, &tok, sizeof(tok));
        prompt->tokens.nbr += 1;
    }
}

static
void shell_prompt(shell_t *shell)
{
    if (get_prompt(shell) == RET_ERROR)
        return;
    tokenize(shell);
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
