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

typedef enum {
    EXPR,
    NONE,
    PIPE,
    SEMICOLON,
    REDIRECT_INPUT,
    REDIRECT_OUTPUT,
    REDIRECT_HERE_DOCUMENT,
    REDIRECT_APPEND_OUTOUT,
} token_type_t;

typedef struct {
    char const *ptr;
    size_t size;
    token_type_t type;
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
    size_t key;
    size_t value;
} env_variable_t;

typedef struct {
    int last_exit_code;
    char working_dir[PATH_MAX];
    bool is_running;
    struct {
        char *data;
        size_t alloc_data;
        env_variable_t *variables;
        size_t count;
    } env;
    prompt_t prompt;
    bool isatty;
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
env_variable_t *my_getenv_var(shell_t *shell, char const *variable);
char *my_getenv(shell_t *shell, char const *variable);
int my_unsetenv(shell_t *shell, char const *variable);
int my_setenv(shell_t *shell, char const *key, char const *data);

/*
 * Init shell.env variables with char **env
 */
int init_env(shell_t *shell, char *const *env);

char **get_envp(shell_t *shell);
char **create_argv(prompt_t const *prompt);

#endif /* MINISHELL_H_ */
