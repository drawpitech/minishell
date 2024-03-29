/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** stack
*/

#include "my/std.h"

#include "execute.h"

void free_stack(cmd_stack_t *stack)
{
    if (stack == NULL)
        return;
    for (cmd_stack_t *ptr = stack; ptr->type != NONE; ptr++)
        if (ptr->type == EXPR && ptr->argv != NULL)
            free(ptr->argv);
    free(stack);
}

cmd_stack_t *create_stack(size_t nbr, token_t tokens[nbr])
{
    cmd_stack_t *stack = malloc((nbr + 1) * sizeof(cmd_stack_t));
    size_t size = 0;

    while (tokens->type != NONE) {
        if (tokens->type == EXPR) {
            stack[size] = (cmd_stack_t){ create_argv(&tokens), EXPR };
            size++;
            continue;
        }
        if (tokens->type != SEMICOLON) {
            stack[size] = (cmd_stack_t){ NULL, tokens->type };
            size++;
        }
        tokens += 1;
    }
    stack[size] = (cmd_stack_t){ NULL, NONE };
    return stack;
}
