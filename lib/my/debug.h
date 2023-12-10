/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** debug
*/

#ifndef DEBUG_H_
    #define DEBUG_H_

    #include "io.h"

    #define NOTHING /* Nothing */

    #ifdef DEBUG_MODE
        #define FORMAT(s) "%s:%d: " s "\n"

        #define HEAD __FILE_NAME__, __LINE__
        #define DEBUG(fmt, ...) (my_printf(FORMAT(fmt), HEAD, __VA_ARGS__))
        #define DEBUG_MSG(string) (my_printf(FORMAT(string), HEAD))
    #else
        #define DEBUG(...) NOTHING
        #define DEBUG_MSG(...) NOTHING
    #endif

#endif /* DEBUG_H_ */
