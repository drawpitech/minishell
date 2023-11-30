/*
** EPITECH PROJECT, 2023
** my_ls
** File description:
** my_ls
*/

#ifndef TEST_LS
    #define TEST_LS

    #include <criterion/criterion.h>
    #include <criterion/redirect.h>

    #include <stdio.h>

    #define SH(cmd) get_stdout("sh -c \"" #cmd "\"")
    #define ENVP environ

extern char **environ;

static inline
void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static inline
char *get_stdout(char const *command)
{
    static char buf[BUFSIZ];
    char *ptr = buf;
    FILE *ls = popen(command, "r");

    while (fgets(ptr, 256, ls) != 0)
        ptr += strlen(ptr);
    pclose(ls);
    return buf;
}

#endif /* TEST_LS */
