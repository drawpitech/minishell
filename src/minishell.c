/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** minishell
*/

#include <stdio.h>
#include <unistd.h>

#include "my/std.h"
#include "my/debug.h"
#include "my/string.h"

#include "minishell.h"

static
void print_prompt(shell_t *shell)
{
    if (!shell->isatty)
        return;
    my_printf("%d > ", shell->last_exit_code);
}

static
int get_prompt(shell_t *shell)
{
    static size_t offset = 0;
    prompt_t *prompt;

    shell->prompt = (prompt_t){ 0 };
    prompt = &shell->prompt;
    print_prompt(shell);
    prompt->size = getline(&prompt->line, &offset, stdin);
    if (prompt->size == (size_t)-1) {
        shell->is_running = false;
        if (shell->isatty)
            my_printf("exit\n");
        return RET_ERROR;
    }
    return RET_VALID;
}

static
token_t *tokenize(shell_t *shell)
{
    prompt_t *prompt = &shell->prompt;
    token_t tok = { 0 };
    char *ptr = prompt->line;

    while (parser_next_token(&ptr, &tok) != NULL) {
        DEBUG("token: [%s]; size: %u; type: %d", tok.ptr, tok.size, tok.type);
        prompt->tokens.tok = my_reallocarray(
            prompt->tokens.tok, prompt->tokens.nbr + 2,
            prompt->tokens.nbr, sizeof(*prompt->tokens.tok)
        );
        my_memcpy(prompt->tokens.tok + prompt->tokens.nbr, &tok, sizeof(tok));
        prompt->tokens.nbr += 1;
    }
    if (prompt->tokens.nbr)
        prompt->tokens.tok[prompt->tokens.nbr].type = NONE;
    return prompt->tokens.tok;
}

static
void shell_prompt(shell_t *shell)
{
    if (get_prompt(shell) == RET_ERROR)
        return;
    if (tokenize(shell) == NULL)
        return;
    if (execute(shell) == RET_ERROR)
        return;
}

static
int get_params(shell_t *shell, int argc, char *const *argv)
{
    int ret;

    if (argc != 3)
        return ret_perror("mysh", "invalid arguments\n");
    if (my_strcmp(argv[1], "-c") != 0)
        return ret_perror("mysh", "unknow arguments `%s`\n", argv[1]);
    shell->prompt.line = argv[2];
    if (tokenize(shell) == NULL)
        return RET_ERROR;
    if (execute(shell) == RET_ERROR)
        return RET_ERROR;
    shell->prompt.line = NULL;
    ret = shell->last_exit_code;
    clear_shell(shell);
    return ret;
}

int minishell(UNUSED int argc, UNUSED char *const *argv, char **env)
{
    shell_t shell = { 0 };

    if (init_env(&shell, env) == RET_ERROR) {
        clear_shell(&shell);
        return RET_ERROR;
    }
    if (argc != 1)
        return get_params(&shell, argc, argv);
    shell.is_running = true;
    shell.isatty = isatty(STDIN_FILENO);
    while (shell.is_running) {
        shell_prompt(&shell);
        clear_prompt(&shell.prompt);
    }
    clear_shell(&shell);
    return RET_VALID;
}
