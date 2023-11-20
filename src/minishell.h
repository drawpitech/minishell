/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** minishell
*/

#ifndef MINISHELL_H_
    #define MINISHELL_H_

    #include <limits.h>
    #include <stdbool.h>
    #include <stddef.h>

typedef struct {
    char const *ptr;
    size_t size;
} token_t;

typedef struct {
    char *line;
    size_t size;
    struct {
        token_t *tok;
        size_t nbr;
    } tokens;
} prompt_t;

typedef struct {
    char working_dir[PATH_MAX];
    bool is_running;
    char *const *env;
    prompt_t prompt;
} shell_t;

/*
 * Entry point of the program.
 **/
int minishell(int argc, char *const *argv, char *const *env);

/*
 * Clear and free params of shell_t pointer.
 **/
void clear_shell(shell_t *shell);

/*
 * Clear and free params of shell_t pointer.
 **/
void clear_prompt(prompt_t *prompt);

/*
 * Get next token of the *ptr string and store it in tok.
 **/
token_t *parser_next_token(char **ptr, token_t *tok);

#endif /* MINISHELL_H_ */
