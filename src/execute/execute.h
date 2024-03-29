/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#ifndef EXECUTE_H_
    #define EXECUTE_H_

    #include "../minishell.h"

    #define IO_MODE (S_IRUSR | S_IWUSR)

typedef struct stack_s {
    char **argv;
    token_type_t type;
} cmd_stack_t;

char const *get_cmd(shell_t *shell, char const *str);
cmd_stack_t *create_stack(size_t nbr, token_t tokens[nbr]);
char **create_argv(token_t *tokens[]);
void free_stack(cmd_stack_t *stack);
int cmd_redirect(shell_t *shell, cmd_stack_t const *stack);
int run_command(shell_t *shell, cmd_stack_t const *stack, int fd[2]);

#endif /* EXECUTE_H_ */
