/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** colors
*/

#ifndef COLORS_H_
    #define COLORS_H_

    #include "io.h"

    #define C_BG(color) ((color) + 10)

    #define C_RESET "\x1b[0m"

enum {
    C_BLK = 30,
    C_RED = 31,
    C_GRN = 32,
    C_YEL = 33,
    C_BLU = 34,
    C_MAG = 35,
    C_CYN = 36,
    C_WHT = 37,
};

enum {
    C_NORM = 0,
    C_BOLD = 1,
    C_UNDR = 2,
};

static inline __attribute__((__used__))
void put_color(char color, char style, char bg)
{
    static char buf_withbg[] = "\x1b[00;30;00m";
    static char buf_nobg[] = "\x1b[00;30m";
    char *ptr = buf_nobg;

    if (bg) {
        ptr = buf_withbg;
        ptr[8] = CHR(C_BG(bg) / 10);
        ptr[9] = CHR(C_BG(bg) % 10);
    }
    ptr[3] = CHR(style);
    ptr[5] = CHR(color / 10);
    ptr[6] = CHR(color % 10);
    my_putstr(ptr);
}

#endif /* COLORS_H_ */
