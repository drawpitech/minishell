/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#ifndef EXECUTE_H_
    #define EXECUTE_H_

    #include "../minishell.h"

typedef struct stack_s {
    char **argv;
    token_type_t type;
} cmd_stack_t;

char const *get_cmd(shell_t *shell, char const *str);
cmd_stack_t *create_stack(size_t nbr, token_t tokens[nbr]);

#endif /* EXECUTE_H_ */
