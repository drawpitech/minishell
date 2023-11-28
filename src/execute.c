/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** execute
*/

#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtins/builtins.h"
#include "debug.h"
#include "my.h"

#include "minishell.h"

static
size_t sum_length(prompt_t const *prompt)
{
    size_t sum = prompt->tokens.nbr;

    for (size_t i = 0; i < prompt->tokens.nbr; i++)
        sum += prompt->tokens.tok[i].size;
    return sum;
}

static
bool is_file_in_dir(char const *dir, char const *file)
{
    struct dirent *dirent = NOT_NULL;
    DIR *dirp = opendir(dir);

    if (dirp == NULL)
        return false;
    while (dirent != NULL) {
        dirent = readdir(dirp);
        if (dirent == NULL)
            break;
        if (my_strcmp(file, dirent->d_name) != 0)
            continue;
        DEBUG("dir: %s", dir);
        closedir(dirp);
        return true;
    }
    closedir(dirp);
    return false;
}

static
char *get_file_in_dir(char **env_path, char const *file)
{
    static char dirpath[PATH_MAX];
    char *tmp = my_strfind(*env_path, ':');
    size_t offset = (tmp == NULL)
        ? my_strlen(*env_path)
        : (size_t)(tmp - *env_path);

    my_strncpy(dirpath, *env_path, offset);
    dirpath[offset] = '\0';
    *env_path += offset + (tmp != NULL);
    return (is_file_in_dir(dirpath, file))
        ? get_fullpath(dirpath, file, dirpath)
        : NULL;
}

static
char *get_cmd_in_path(shell_t *shell, char const *cmd)
{
    env_variable_t *env_path;
    char *fullpath;

    if (cmd == NULL)
        return NULL;
    env_path = my_getenv(shell, "PATH");
    if (env_path == NULL) {
        ret_perror("mysh", "variable 'PATH' missing.");
        return NULL;
    }
    for (char *ptr = env_path->value; *ptr;) {
        fullpath = get_file_in_dir(&ptr, cmd);
        if (fullpath != NULL)
            return fullpath;
    }
    return NULL;
}

static
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
        my_strncpy(ptr, tokens[i].ptr, tokens[i].size);
        ptr[tokens[i].size] = '\0';
        ptr += tokens[i].size + 1;
    }
    argv[prompt->tokens.nbr] = NULL;
    return argv;
}

static
char const *get_cmd(shell_t *shell, char const *str)
{
    char *cmd;

    for (size_t i = 0; str[i]; i++)
        if (str[i] == '/')
            return str;
    cmd = get_cmd_in_path(shell, str);
    if (cmd != NULL)
        return cmd;
    ret_perror(str, "Command not found.\n");
    return NULL;
}

static
int return_value(int wstatus)
{
    if (WIFEXITED(wstatus))
        return WEXITSTATUS(wstatus);
    if (WIFSIGNALED(wstatus)) {
        my_printf("%s\n", strsignal(WTERMSIG(wstatus)));
        return SH_FATAL_CODE_SIGNAL + WTERMSIG(wstatus);
    }
    if (WIFSTOPPED(wstatus)) {
        my_printf("%s\n", strsignal(WSTOPSIG(wstatus)));
        return WSTOPSIG(wstatus);
    }
    if (WIFCONTINUED(wstatus))
        my_printf("Continued\n");
    return SH_CODE_SUCCES;
}

static
int run_external_cmd(shell_t *shell, char const *cmd, char **argv)
{
    pid_t child_pid = fork();
    int wstatus;
    char **env;

    if (child_pid == -1) {
        ret_perror("minishell", NULL);
        return SH_CODE_GENERAL_ERROR;
    }
    if (child_pid == 0) {
        shell->is_running = false;
        env = get_envp(shell);
        execve(cmd, argv, env);
        free(env);
    } else {
        wait(&wstatus);
        return return_value(wstatus);
    }
    return SH_CODE_SUCCES;
}

static
int run_command(shell_t *shell, char **argv)
{
    char const *cmd;
    int ret;
    builtin_cmd_t *builtin = get_builtin(argv[0]);

    if (builtin != NULL) {
        DEBUG("Running builtin %s", argv[0]);
        ret = builtin(shell, argv);
        free(argv);
        return ret;
    }
    cmd = get_cmd(shell, argv[0]);
    if (cmd == NULL) {
        free(argv);
        return SH_CODE_CMD_NOT_FOUND;
    }
    DEBUG("Running %s", cmd);
    ret = run_external_cmd(shell, cmd, argv);
    free(argv);
    return ret;
}

int execute(shell_t *shell)
{
    char **argv;

    if (shell == NULL)
        return RET_ERROR;
    if (shell->prompt.tokens.nbr == 0)
        return RET_VALID;
    argv = create_argv(&shell->prompt);
    if (argv == NULL)
        return RET_ERROR;
    shell->last_exit_code = run_command(shell, argv);
    return RET_VALID;
}
