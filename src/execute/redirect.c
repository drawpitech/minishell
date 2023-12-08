/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** redirect
*/

#include <fcntl.h>
#include <unistd.h>

#include "../builtins/builtins.h"
#include "../debug.h"
#include "execute.h"

#include "my.h"

static
int redirect_stdout(cmd_stack_t const *stack, int flag)
{
    int fd = open(stack->argv[0], O_WRONLY | O_CREAT | flag, IO_MODE);

    dup2(fd, STDOUT_FILENO);
    cmd_redirect(stack);
    return fd;
}

int cmd_redirect(cmd_stack_t const *stack)
{
    switch (stack[1].type) {
        case REDIRECT_OUTPUT:
            return redirect_stdout(stack + 2, O_TRUNC);
        case REDIRECT_APPEND_OUTOUT:
            return redirect_stdout(stack + 2, O_APPEND);
        case EXPR:
        case NONE:
        default:
            return 0;
    }
}
