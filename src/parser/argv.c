/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** argv
*/

#include "my.h"

#include "../debug.h"
#include "../minishell.h"

static
size_t sum_length(prompt_t const *prompt)
{
    size_t sum = prompt->tokens.nbr;

    for (size_t i = 0; i < prompt->tokens.nbr; i++)
        sum += prompt->tokens.tok[i].size;
    return sum;
}

static
char const *get_next_quote(char const *str, size_t size)
{
    char c = *str;

    for (size_t i = 1; i < size; i++) {
        if (str[i] == '\'' && c != '"')
            return str + i;
        if (str[i] == '"' && c != '\'')
            return str + i;
    }
    return str + size;
}

static
void create_arg(token_t const *token, char *ptr)
{
    char const *str;
    size_t size;

    for (size_t i = 0; i < token->size; i++) {
        str = token->ptr + i;
        size = get_next_quote(str, token->size - i) - str;
        if (*str == '\'' || *str == '"') {
            str += 1;
            size -= 1;
            i += 1;
        }
        my_strncpy(ptr, str, size);
        ptr += size;
        i += size;
    }
    *ptr = '\0';
}

char **create_argv(prompt_t const *prompt)
{
    token_t *tokens = prompt->tokens.tok;
    size_t offset_argv = (prompt->tokens.nbr + 1) * sizeof(char *);
    char **argv = malloc(offset_argv + sum_length(prompt) * sizeof(char));
    char *ptr;

    if (argv == NULL)
        return NULL;
    ptr = (char *)argv + offset_argv;
    for (size_t i = 0; i < prompt->tokens.nbr; i++) {
        argv[i] = ptr;
        create_arg(tokens + i, ptr);
        ptr += tokens[i].size + 1;
    }
    argv[prompt->tokens.nbr] = NULL;
    for (int i = 0; argv[i] != NULL; i++)
        DEBUG("argv[%d]: `%s`", i, argv[i]);
    return argv;
}
