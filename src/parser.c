/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** parser
*/

#include <stddef.h>

#include "my.h"

#include "minishell.h"

static
char *find_the_end_of_this(char *start)
{
    for (; *start != '\0'
        && (*start != ' ' && *start != '\t')
        && *start != '\n'
        ; start++);
    return start;
}

static
char *get_end(char **start, bool *is_quoted)
char *get_end(char **start)
{
    char *end = NULL;

    switch (**start) {
        case '\0':
            return NULL;
        case '"':
        case '\'':
            end = my_strfind(*start + 1, **start);
            if (end == NULL)
                break;
            *start += 1;
            break;
        default:
            end = find_the_end_of_this(*start);
            break;
    }
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
        .size = end - start - (end[-1] == '\'' || end[-1] == '"'),
    };
    return tok;
}
