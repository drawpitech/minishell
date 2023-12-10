/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "my/std.h"
#include "my/debug.h"

#include "../builtins/builtins.h"
#include "execute.h"

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

static
void child_process(
    shell_t *shell,
    char const *cmd,
    cmd_stack_t const *stack,
    int fd[2])
{
    char **env;

    if (fd != NULL) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
    }
    shell->is_running = false;
    if (cmd_redirect(shell, stack) == RET_ERROR)
        return;
    env = get_envp(shell);
    execve(cmd, stack->argv, env);
}

static
int parent_process(int fd[2])
{
    int wstatus = 0;

    if (fd == NULL) {
        wait(&wstatus);
    } else {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
    }
    return return_value(wstatus);
}

static
int run_external_cmd(
    shell_t *shell,
    char const *cmd,
    cmd_stack_t const *stack,
    int fd[2])
{
    pid_t child_pid = fork();

    if (child_pid == -1) {
        ret_perror("minishell", NULL);
        return SH_CODE_GENERAL_ERROR;
    }
    if (child_pid == 0) {
        child_process(shell, cmd, stack, fd);
    } else {
        return parent_process(fd);
    }
    return SH_CODE_SUCCES;
}

int run_command(shell_t *shell, cmd_stack_t const *stack, int fd[2])
{
    char const *cmd;
    char **argv = stack->argv;
    builtin_cmd_t *builtin = get_builtin(argv[0]);

    if (builtin != NULL) {
        DEBUG("Running builtin %s", argv[0]);
        return builtin(shell, argv);
    }
    cmd = get_cmd(shell, argv[0]);
    if (cmd == NULL)
        return SH_CODE_CMD_NOT_FOUND;
    DEBUG("Running %s", cmd);
    return run_external_cmd(shell, cmd, stack, fd);
}

static
bool is_stack_valid(cmd_stack_t *stack)
{
    int i = 0;

    if (stack[0].type == NONE)
        return true;
    for (; stack[i + 1].type != NONE; i++) {
        if (stack[i].type == EXPR || stack[i + 1].type == EXPR)
            continue;
        i++;
        break;
    }
    if (stack[i].type == EXPR)
        return true;
    my_dprintf(STDERR_FILENO, (stack[i].type == PIPE)
        ? "Invalid null command.\n"
        : "Missing name for redirect.\n");
    free_stack(stack);
    return false;
}

int execute(shell_t *shell)
{
    cmd_stack_t *stack;

    if (shell == NULL)
        return RET_ERROR;
    if (shell->prompt.tokens.nbr == 0)
        return RET_VALID;
    stack = create_stack(shell->prompt.tokens.nbr, shell->prompt.tokens.tok);
    if (!is_stack_valid(stack))
        return RET_ERROR;
    for (cmd_stack_t *ptr = stack; ptr->type != NONE; ptr++) {
        DEBUG("%d", ptr->type);
        if (ptr->type == EXPR)
            shell->last_exit_code = run_command(shell, ptr, NULL);
        else
            ptr++;
    }
    free_stack(stack);
    return RET_VALID;
}
