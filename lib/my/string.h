/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** string
*/

#ifndef MY_STRING_H_
    #define MY_STRING_H_

    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>

    #define IS_LOWERCASE(c) ((c) >= 'a' && (c) <= 'z')
    #define IS_UPPERCASE(c) ((c) >= 'A' && (c) <= 'Z')
    #define IS_ALPHA(c) (IS_LOWERCASE(c) || IS_UPPERCASE(c))
    #define IS_NUM(c) ((c) >= '0' && (c) <= '9')
    #define IS_ALPHANUM(c) (IS_NUM(c) || IS_ALPHA(c))
    #define IS_PRINTABLE(c) ((c) >= ' ' && (c) <= '~')

    #define CH_LOW(c) (IS_UPPERCASE(c) ? ((c) + 32) : (c))
    #define CH_UPP(c) (IS_LOWERCASE(c) ? ((c) - 32) : (c))

    #define BASE_BIN "01"
    #define BASE_OCT "01234567"
    #define BASE_DEC "0123456789"
    #define BASE_HEX "0123456789abcdef"
    #define BASE_HEX_MIN "0123456789abcdef"
    #define BASE_HEX_MAJ "0123456789ABCDEF"

bool my_memassert(const void *got, const void *expect, size_t n);
bool my_str_isalpha(char const *str);
bool my_str_islower(char const *str);
bool my_str_isnum(char const *str);
bool my_str_isprintable(char const *str);
bool my_str_isupper(char const *str);
bool my_str_startswith(const char *big, const char *little);
char *convert_base(char const *, char const *, char const *);
char *get_fullpath(char const *directory, char const *filename, char *result);
char *my_nbr_to_base(int nbr, char const *base);
char *my_revstr(char *src);
char *my_str_join(size_t argc, char *const *argv, char const *separator);
char *my_strapp(char **dest, char const *src);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strfind(char *str, char c);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, size_t nb);
char *my_strncpy(char *dest, char const *src, size_t n);
char *my_strndup(char const *src, size_t n);
char *my_strpbrk(char *str, char const *chars);
char *my_strupcase(char *str);
char const *my_strstr(char const *str, char const *to_find);
int my_show_word_array(char *const *tab);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, size_t n);
int str_to_int(char const *str);
int str_to_int_base(char const *str, char const *base);
size_t my_memfind(const void *arr, const void *target, size_t n);
size_t my_strlen(char const *str);
size_t write_int_base(long long nbr, char const *base, char *buf);
size_t write_uint_base(unsigned long long nbr, char const *base, char *buf);
void *my_memcpy(void *restrict dest, const void *restrict src, size_t n);
void *my_memset(void *s, int c, size_t n);
void *reverse_arr(uint32_t size, void *arr, size_t memsize);

#endif /* MY_STRING_H_ */
