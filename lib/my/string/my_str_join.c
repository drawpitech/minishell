/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** my_str_join
*/

#include "string.h"
#include "std.h"

static
size_t len_str_arr(char *const *arr, size_t size)
{
    size_t len = 0;

    for (; size; size--)
        len += my_strlen(arr[size]);
    return len;
}

char *my_str_join(size_t argc, char *const *argv, char const *separator)
{
    char *dest;

    if (argv == NULL || separator == NULL)
        return NULL;
    dest = malloc(
        (len_str_arr(argv, argc) + ((argc - 1) * my_strlen(separator) + 1)
        * sizeof(char)));
    dest[0] = '\0';
    for (size_t i = 0; i < argc - 1; i++) {
        if (argv[i] == NULL)
            continue;
        my_strcat(dest, argv[i]);
        my_strcat(dest, separator);
    }
    my_strcat(dest, argv[argc - 1]);
    return dest;
}
