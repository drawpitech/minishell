/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** flag_utils
*/

#include "io.h"
#include "std.h"
#include "string.h"

#include "internal.h"

static
void add_padding(printf_t *pr, size_t length)
{
    char *pad = malloc((length + 1) * sizeof(char));

    my_memset(pad, ' ', length);
    pad[length] = '\0';
    add_in_buf(pr, pad);
    free(pad);
}

void write_flag(printf_t *pr, printf_args_t const *arg, char const *buf)
{
    size_t len = my_strlen(buf);

    if (arg->flags.padded && arg->flags.padding - (int)len > 0)
        add_padding(pr, arg->flags.padding - len);
    add_in_buf(pr, buf);
    if (arg->flags.padded && arg->flags.padding - (int)len < 0)
        add_padding(pr, -arg->flags.padding - len);
}

static
size_t new_size(size_t old, size_t add)
{
    size_t new = (old) ? old : 2;

    while (old + add + 1 > new)
        new *= 2;
    return new;
}

void add_in_buf(printf_t *pr, char const *text_buf)
{
    buffer_t *buf = &pr->buf;
    size_t len = my_strlen(text_buf);
    size_t new = new_size(buf->size, len);

    if (new != buf->alloc_size) {
        buf->alloc_size = new;
        buf->str = my_reallocarray(
            buf->str, pr->buf.alloc_size,
            buf->size + 1, sizeof(char));
        if (buf->size == 0)
            buf->str[0] = '\0';
    }
    buf->size += len;
    my_strcat(buf->str, text_buf);
}

void print_till_purcent(printf_t *pr)
{
    char const *ptr = pr->format + pr->index;
    char const *end = my_strstr(ptr + 1, "%");
    char *buf = NULL;

    if (end == NULL) {
        add_in_buf(pr, ptr);
        pr->index += my_strlen(ptr);
        return;
    }
    buf = my_strndup(ptr, end - ptr);
    buf[end - ptr] = '\0';
    add_in_buf(pr, buf);
    pr->index += end - ptr;
    free(buf);
}
