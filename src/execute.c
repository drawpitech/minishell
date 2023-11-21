/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
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
    size_t offset_argv = (prompt->tokens.nbr + 1) * sizeof(char *);
    char **argv = malloc(offset_argv + sum_length(prompt) * sizeof(char));
    char *ptr;

    if (argv == NULL)
        return NULL;
    ptr = (char *)argv + offset_argv;
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

    if (child_pid == -1) {
        free(argv);
        return ret_perror("minishell", NULL);
    }
    if (child_pid == 0) {
        shell->is_running = false;
        execve(argv[0], argv, shell->env);
    }
    free(argv);
    return RET_VALID;
}

static
int return_value(int wstatus)
{
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if (WIFSIGNALED(wstatus)) {
        my_printf("%s\n", strsignal(WTERMSIG(wstatus)));
        return SH_FATAL_CODE_SIGNAL + WTERMSIG(wstatus);
    }
    if (WIFSTOPPED(wstatus)) {
        my_printf("%s\n", strsignal(WSTOPSIG(wstatus)));
        return WSTOPSIG(wstatus);
    }
    if (WIFCONTINUED(wstatus))
        my_printf("Continued\n");
    return SH_CODE_SUCCES;
}

int execute(shell_t *shell)
{
    char **argv;
    int wstatus;

    if (shell == NULL)
        return RET_ERROR;
    if (shell->prompt.tokens.nbr == 0)
        return RET_VALID;
    argv = create_argv(&shell->prompt);
    if (argv == NULL || run_command(shell, argv) == RET_ERROR)
        return RET_ERROR;
    wait(&wstatus);
    shell->last_exit_code = return_value(wstatus);
    return RET_VALID;
}
