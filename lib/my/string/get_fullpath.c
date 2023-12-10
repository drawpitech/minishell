/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** get_fullpath
*/

#include "string.h"

char *get_fullpath(char const *directory, char const *filename, char *result)
{
    if (directory == NULL || filename == NULL || result == NULL)
        return NULL;
    if (filename[0] != '/' && filename[0] != '~') {
        if (result != directory)
            result[0] = '\0';
        my_strcpy(result, directory);
        if (directory[my_strlen(directory) - 1] != '/')
            my_strcat(result, "/");
        my_strcat(result, filename);
    } else {
        my_strcpy(result, filename);
    }
    return result;
}
