/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** lexer
*/

#include "my.h"

#include "minishell.h"

static
char *get_word(char *start)
{
    char *end = start;

    while (end != NULL
        && *end != '\0'
        && *end != ' '
        && *end != '\t'
        && *end != '\n'
        && *end != '|'
        && *end != ';'
        && *end != '<'
        && *end != '>'
        ) {
        if (*end == '\'' || *end == '"')
            end = my_strfind(end + 1, *end);
        if (end != NULL)
            end += 1;
    }
    return end;
}

static
token_type_t parse_redirection(char c, char **ptr)
{
    switch (c) {
        case '|':
            (*ptr) += 1;
            return PIPE;
        case ';':
            (*ptr) += 1;
            return SEMICOLON;
        case '<':
            if ((*ptr)[1] == (*ptr)[0]) {
                *ptr += 2;
                return REDIRECT_HERE_DOCUMENT;
            }
            *ptr += 1;
            return REDIRECT_INPUT;
        default:
            return NONE;
    }
}

static
token_type_t get_end(char **ptr)
{
    char *tmp;

    switch ((*ptr)[0]) {
        case '\0':
            return NONE;
        case ';':
        case '|':
        case '<':
            return parse_redirection((*ptr)[0], ptr);
        case '>':
            return parse_redirection('<', ptr) + 1;
        default:
            tmp = get_word(*ptr);
            *ptr = (tmp == NULL)
                ? NULL
                : tmp + (*tmp == '\'' || *tmp == '"');
            return EXPR;
    }
}

token_t *parser_next_token(char **ptr, token_t *tok)
{
    char *start = NULL;
    char *end = NULL;
    token_type_t type;

    if (ptr == NULL || tok == NULL)
        return NULL;
    for (; **ptr == ' ' || **ptr == '\n' || **ptr == '\t'; *ptr += 1);
    start = *ptr;
    end = start;
    type = get_end(&end);
    if (type == NONE || end == NULL || *start == '\0')
        return NULL;
    *ptr = end;
    *tok = (token_t){
        .ptr = start,
        .size = end - start,
        .type = type,
    };
    return tok;
}
