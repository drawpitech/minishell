/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#include <stddef.h>
#include <stdlib.h>

#include "my.h"

#include "minishell.h"

static
size_t sum_length(prompt_t const *prompt)
{
    size_t sum = prompt->tokens.nbr;

    for (size_t i = 0; i < prompt->tokens.nbr; i++)
        sum += prompt->tokens.tok[i].size;
    return sum;
}

static
char **create_argv(prompt_t const *prompt)
{
    token_t *tokens = prompt->tokens.tok;
    char *raw_buf = malloc(sum_length(prompt) * sizeof(char));
    char *ptr = raw_buf;
    char **argv;

    if (raw_buf == NULL)
        return NULL;
    argv = malloc((prompt->tokens.nbr + 1) * sizeof(char *));
    if (argv == NULL) {
        free(argv);
        return NULL;
    }
    for (size_t i = 0; i < prompt->tokens.nbr; i++) {
        argv[i] = ptr;
        my_strncpy(ptr, tokens[i].ptr, tokens[i].size);
        ptr[tokens[i].size] = '\0';
        ptr += tokens[i].size + 1;
    }
    argv[prompt->tokens.nbr] = NULL;
    return argv;
}

void execute(shell_t *shell)
{
    char **argv;

    if (shell == NULL || shell->prompt.tokens.nbr == 0)
        return;
    argv = create_argv(&shell->prompt);
    if (argv == NULL || argv[0] == NULL)
        return;
    free(argv[0]);
    free(argv);
}
