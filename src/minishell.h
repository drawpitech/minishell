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
    int last_exit_code;
    char working_dir[PATH_MAX];
    bool is_running;
    char **env;
    prompt_t prompt;
} shell_t;

enum {
    SH_CODE_SUCCES = 0,
    SH_CODE_GENERAL_ERROR = 1,
    SH_CODE_CANNOT_EXEC = 126,
    SH_CODE_CMD_NOT_FOUND = 127,
    SH_FATAL_CODE_SIGNAL = 128,
};


/*
 * Entry point of the program.
 **/
int minishell(int argc, char *const *argv, char **env);

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

/*
 * Run command passed as shell->prompt
 */
int execute(shell_t *shell);

/*
 * Get a variable in the environment, and return the value.
 * Searches: "$(variable)=*"
 */
char *my_getenv(char **env, char const *variable);

/*
 * Get the fullpath of the cmd if found the the PATH variable.
 **/
char *get_cmd_in_path(char const *cmd, char **env);

#endif /* MINISHELL_H_ */
