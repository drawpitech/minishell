/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

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
int run_external_cmd(shell_t *shell, char const *cmd, cmd_stack_t **stack)
{
    pid_t child_pid = fork();
    int wstatus;
    char **env;

    if (child_pid == -1) {
        ret_perror("minishell", NULL);
        return SH_CODE_GENERAL_ERROR;
    }
    if (child_pid == 0) {
        shell->is_running = false;
        env = get_envp(shell);
        execve(cmd, (*stack)->argv, env);
        free(env);
    } else {
        wait(&wstatus);
        return return_value(wstatus);
    }
    return SH_CODE_SUCCES;
}

static
int run_command(shell_t *shell, cmd_stack_t **stack)
{
    char const *cmd;
    int ret;
    char **argv = (*stack)->argv;
    builtin_cmd_t *builtin = get_builtin(argv[0]);

    if (builtin != NULL) {
        DEBUG("Running builtin %s", argv[0]);
        ret = builtin(shell, argv);
        free(argv);
        return ret;
    }
    cmd = get_cmd(shell, argv[0]);
    if (cmd == NULL) {
        free(argv);
        return SH_CODE_CMD_NOT_FOUND;
    }
    DEBUG("Running %s", cmd);
    ret = run_external_cmd(shell, cmd, stack);
    free(argv);
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
        switch (ptr->type) {
            case EXPR:
                shell->last_exit_code = run_command(shell, &ptr);
                continue;
            default:
                continue;
        }
    }
    free(stack);
    return RET_VALID;
}
