/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtins/builtins.h"
#include "../debug.h"
#include "execute.h"

#include "my.h"

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

static
void child_process(shell_t *shell, char const *cmd, cmd_stack_t const *stack)
{
    char **env;

    cmd_redirect(stack);
    shell->is_running = false;
    env = get_envp(shell);
    execve(cmd, stack->argv, env);
}

static
int run_external_cmd(shell_t *shell, char const *cmd, cmd_stack_t const *stack)
{
    pid_t child_pid = fork();
    int wstatus;

    if (child_pid == -1) {
        ret_perror("minishell", NULL);
        return SH_CODE_GENERAL_ERROR;
    }
    if (child_pid == 0) {
        child_process(shell, cmd, stack);
    } else {
        wait(&wstatus);
        return return_value(wstatus);
    }
    return SH_CODE_SUCCES;
}

static
int run_command(shell_t *shell, cmd_stack_t const *stack)
{
    char const *cmd;
    int ret;
    char **argv = stack->argv;
    builtin_cmd_t *builtin = get_builtin(argv[0]);

    if (builtin != NULL) {
        DEBUG("Running builtin %s", argv[0]);
        ret = builtin(shell, argv);
        return ret;
    }
    cmd = get_cmd(shell, argv[0]);
    if (cmd == NULL)
        return SH_CODE_CMD_NOT_FOUND;
    DEBUG("Running %s", cmd);
    ret = run_external_cmd(shell, cmd, stack);
    return ret;
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
            shell->last_exit_code = run_command(shell, ptr);
        else
            ptr++;
    }
    free_stack(stack);
    return RET_VALID;
}
