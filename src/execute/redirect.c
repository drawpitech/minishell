/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** redirect
*/

#include <fcntl.h>
#include <unistd.h>

#include "my/std.h"

#include "execute.h"

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

static
int redirect_stdin(cmd_stack_t const *stack)
{
    int file = open(stack->argv[0], O_RDONLY, IO_MODE);
    int fd[2];
    const ssize_t buff_size = 10;
    char buff[buff_size + 1];
    ssize_t n;

    if (file == -1) {
        ret_perror(stack->argv[0], "No such file or directory.");
        return -1;
    }
    pipe(fd);
    dup2(fd[0], STDIN_FILENO);
    do {
        n = read(file, buff, buff_size);
        write(fd[1], buff, n);
    } while (n == buff_size);
    close(file);
    close(fd[0]);
    close(fd[1]);
    return 0;
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
        case REDIRECT_INPUT:
            return redirect_stdin(stack + 2);
        case EXPR:
        case NONE:
        default:
            return 0;
    }
}
