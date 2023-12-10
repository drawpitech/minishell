/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** malloc
*/

#include "std.h"
#include "string.h"

void *my_calloc(size_t nmemb, size_t size)
{
    void *ptr = malloc(nmemb * size);

    if (ptr == NULL)
        return NULL;
    my_memset(ptr, 0, nmemb * size);
    return ptr;
}

void *my_realloc(void *ptr, size_t size, size_t old)
{
    void *new;

    if (size == 0) {
        if (ptr != NULL)
            free(ptr);
        return NULL;
    }
    new = malloc(size);
    if (ptr == NULL || new == NULL)
        return new;
    my_memcpy(new, ptr, old);
    free(ptr);
    return new;
}

void *my_reallocarray(void *ptr, size_t nmemb, size_t nmemb_old, size_t size)
{
    return my_realloc(ptr, nmemb * size, nmemb_old * size);
}
