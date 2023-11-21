/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#include <stddef.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

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

static
int run_command(shell_t *shell, char **argv)
{
    pid_t child_pid = fork();
    int wstatus;

    if (child_pid == -1)
        return ret_perror("minishell", NULL);
    if (child_pid == 0) {
        shell->is_running = false;
        return execve(argv[0], argv, shell->env);
    }
    wait(&wstatus);
    return RET_VALID;
}

void execute(shell_t *shell)
{
    char **argv;

    if (shell == NULL || shell->prompt.tokens.nbr == 0)
        return;
    argv = create_argv(&shell->prompt);
    if (argv == NULL)
        return;
    run_command(shell, argv);
    free(argv[0]);
    free(argv);
}
