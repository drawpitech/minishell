/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** lexer
*/

#include "my.h"

#include "../minishell.h"

static
char *get_word(char **start)
{
    char *end = *start;

    while (*end != '\0'
        && *end != ' '
        && *end != '\t'
        && *end != '\n'
        ) {
        if (*end == '\'' || *end == '"')
            end = my_strfind(end + 1, *end);
        end += 1;
    }
    return end;
}

static
char *get_end(char **start)
{
    char *end = NULL;

    if (**start == '\0')
        return NULL;
    end = get_word(start);
    return (end == NULL)
        ? *start + my_strlen(*start)
        : end + (*end == '\'' || *end == '"');
}

token_t *parser_next_token(char **ptr, token_t *tok)
{
    char *start = NULL;
    char *end = NULL;

    if (ptr == NULL || tok == NULL)
        return NULL;
    for (; **ptr == ' ' || **ptr == '\n' || **ptr == '\t'; *ptr += 1);
    start = *ptr;
    end = get_end(&start);
    if (end == NULL || *start == '\0')
        return NULL;
    *ptr = end;
    *tok = (token_t){
        .ptr = start,
        .size = end - start,
    };
    return tok;
}
