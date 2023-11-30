/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** bob
*/

#include <stdio.h>

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "tests.h"
#include "../src/minishell.h"

Test(working, ls, .init=cr_redirect_stdout) {
    char *expected = SH(ls);

    minishell(3, (char *[3]){"./mysh", "-c", "ls"}, ENVP);
    cr_assert_stdout_eq_str(expected);
}

Test(working, echo, .init=cr_redirect_stdout) {
    char *expected = SH(echo "bob");

    minishell(3, (char *[3]){"./mysh", "-c", "echo \"bob\""}, ENVP);
    cr_assert_stdout_eq_str(expected);
}
