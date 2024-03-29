/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** argv
*/

#include "my/debug.h"
#include "my/string.h"

#include "execute.h"

static
size_t sum_length(token_t tokens[])
{
    size_t sum = 0;

    for (; tokens->type == EXPR; tokens++)
        sum += (tokens->size + 1) * sizeof(char);
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

static
size_t count_tokens(token_t tokens[])
{
    size_t size = 0;

    for (; tokens[size].type == EXPR; size++);
    return size;
}

char **create_argv(token_t *tokens[])
{
    size_t off_tokens = (1 + count_tokens(*tokens)) * sizeof(char *);
    char **argv = malloc(sum_length(*tokens) + off_tokens);
    char *ptr;
    size_t i = 0;

    if (argv == NULL)
        return NULL;
    ptr = (char *)argv + off_tokens;
    for (; (*tokens)->type == EXPR; i++) {
        argv[i] = ptr;
        create_arg(*tokens, ptr);
        ptr += (*tokens)->size + 1;
        *tokens += 1;
    }
    argv[i] = NULL;
    for (i = 0; argv[i] != NULL; i++)
        DEBUG("argv[%d]: `%s`", i, argv[i]);
    return argv;
}
