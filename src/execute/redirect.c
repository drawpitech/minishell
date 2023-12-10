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
