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

int cmd_redirect(cmd_stack_t const *stack)
{
    int fd;
    mode_t mode = S_IRUSR | S_IWUSR;
    int flag_wr = O_WRONLY | O_CREAT;

    switch (stack[1].type) {
        case REDIRECT_OUTPUT:
            fd = open(stack[2].argv[0], flag_wr | O_TRUNC, mode);
            dup2(fd, STDOUT_FILENO);
            return fd;
        case REDIRECT_APPEND_OUTOUT:
            fd = open(stack[2].argv[0], flag_wr | O_APPEND, mode);
            dup2(fd, STDOUT_FILENO);
            return fd;
        case EXPR:
        case NONE:
        default:
            return 0;
    }
}
