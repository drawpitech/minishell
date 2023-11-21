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

#include "debug.h"
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
char const *get_cmd(char const *str, char **env)
{
    char *cmd;

    for (size_t i = 0; str[i]; i++)
        if (str[i] == '/')
            return str;
    cmd = get_cmd_in_path(str, env);
    if (cmd != NULL)
        return cmd;
    ret_perror(str, "Command not found.\n");
    return NULL;
}

static
int run_command(shell_t *shell, char **argv)
{
    pid_t child_pid;
    char const *cmd = get_cmd(argv[0], shell->env);

    if (cmd == NULL) {
        free(argv);
        return SH_CODE_CMD_NOT_FOUND;
    }
    DEBUG("Running %s", cmd);
    child_pid = fork();
    if (child_pid == -1) {
        free(argv);
        ret_perror("minishell", NULL);
        return SH_CODE_GENERAL_ERROR;
    }
    if (child_pid == 0) {
        shell->is_running = false;
        execve(cmd, argv, shell->env);
    }
    free(argv);
    return SH_CODE_SUCCES;
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
    if (argv == NULL)
        return RET_ERROR;
    shell->last_exit_code = run_command(shell, argv);
    wait(&wstatus);
    if (shell->last_exit_code == SH_CODE_SUCCES)
        shell->last_exit_code = return_value(wstatus);
    return RET_VALID;
}
