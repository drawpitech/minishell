/*
** EPITECH PROJECT, 2023
** minishell
** File description:
** math
*/

#ifndef MY_MATH_H_
    #define MY_MATH_H_

    #include <stdbool.h>
    #include <stdint.h>

    #define MIN(x, y) (((x) < (y)) ? (x) : (y))
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))
    #define ABS(n) (((n) > 0) ? (n) : -(n))

bool my_is_prime(int nb);
int my_sqrt(int nb);
uint32_t my_pow(uint32_t x, uint32_t y);

#endif /* MY_MATH_H_ */
