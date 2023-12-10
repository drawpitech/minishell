/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** redirect
*/

#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtins/builtins.h"
#include "../debug.h"
#include "execute.h"

#include "my.h"

static
int run_external_cmd(
    shell_t *shell,
    char const *cmd,
    cmd_stack_t const *stack,
    int fd[2])
{
    pid_t child_pid = fork();
    int wstatus = 0;

    if (child_pid == -1) {
        ret_perror("minishell", NULL);
        return SH_CODE_GENERAL_ERROR;
    }
    if (child_pid == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        child_process(shell, cmd, stack);
    } else {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        return return_value(wstatus);
    }
    return SH_CODE_SUCCES;
}

static
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
int redirect_pipe(shell_t *shell, cmd_stack_t const *stack)
{
    int fd[2];

    pipe(fd);
    shell->last_exit_code = run_command(shell, stack, fd);
    return 0;
}

static
int redirect_stdout(shell_t *shell, cmd_stack_t const *stack, int flag)
{
    int fd = open(stack->argv[0], O_WRONLY | O_CREAT | flag, IO_MODE);

    dup2(fd, STDOUT_FILENO);
    cmd_redirect(shell, stack);
    return fd;
}

int cmd_redirect(shell_t *shell, cmd_stack_t const *stack)
{
    switch (stack[1].type) {
        case REDIRECT_OUTPUT:
            return redirect_stdout(shell, stack + 2, O_TRUNC);
        case REDIRECT_APPEND_OUTOUT:
            return redirect_stdout(shell, stack + 2, O_APPEND);
        case PIPE:
            return redirect_pipe(shell, stack + 2);
        case EXPR:
        case NONE:
        default:
            return 0;
    }
}
