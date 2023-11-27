##
## EPITECH PROJECT, 2023
## minishell
## File description:
## Makefile
##

# ↓ Basic variables
CC := gcc -std=gnu11
CFLAGS := -W -Wall -Wextra -Wunused -Wpedantic
CFLAGS += -Wundef -Wshadow -Wcast-align
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Waggregate-return -Wcast-qual
CFLAGS += -Wunreachable-code
CFLAGS += -U_FORTIFY_SOURCE
CFLAGS += -iquote ./

# ↓ Binaries
NAME := libmy.a

# Source files
VPATH := .
SRC := my_putchar.c
SRC += my_putstr.c
SRC += reverse.c
SRC += my_showmem.c
SRC += my_showstr.c
SRC += my_strcat.c
SRC += my_strcmp.c
SRC += my_strcpy.c
SRC += my_strlen.c
SRC += my_strstr.c
SRC += my_strpbrk.c
SRC += str_identify.c
SRC += strcases.c
SRC += str_to_int.c
SRC += my_nbr_to_base.c
SRC += my_strdup.c
SRC += my_str_join.c
SRC += my_show_word_array.c
SRC += convert_base.c
SRC += get_color.c
SRC += my_nbr_len.c
SRC += my_str_startswith.c
SRC += return_err.c
SRC += get_fullpath.c
SRC += mem.c
SRC += malloc.c
SRC += qsort.c
SRC += write_number.c

SRC += math/my_pow.c
SRC += math/my_sqrt.c
SRC += math/my_is_prime.c

SRC += my_printf/families/printf.c
SRC += my_printf/families/sprintf.c
SRC += my_printf/families/asprintf.c
SRC += my_printf/families/dprintf.c
SRC += my_printf/flag_parser.c
SRC += my_printf/flag_utils.c
SRC += my_printf/convertors/char.c
SRC += my_printf/convertors/float.c
SRC += my_printf/convertors/int.c
SRC += my_printf/convertors/ptr.c
SRC += my_printf/convertors/str.c
SRC += my_printf/convertors/unsigned.c
SRC += my_printf/convertors/len.c

# ↓ Objects
BUILD_DIR := .build
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

# ↓ Dependencies for headers
DEPS_FLAGS := -MMD -MP
DEPS := $(OBJ:.o=.d)

DIE := exit 1
# ↓ Colors
ECHO := echo -e
C_RESET := \033[00m
C_BOLD := \e[1m
C_RED := \e[31m
C_GREEN := \e[32m
C_YELLOW := \e[33m
C_BLUE := \e[34m
C_PURPLE := \e[35m
C_CYAN := \e[36m

all: $(NAME)

.PHONY: all

# ↓ Compiling
$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(NAME): $(HEADER) $(OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}AR${C_RESET}] ${C_RED}$@${C_RESET}"
	@ $(AR) rc $@ $(OBJ) || $(DIE)
	@ cp $@ ..
	@ mkdir -p ../../include
	@ cp my.h ../../include/
	@ cp colors.h ../../include/

# ↓ Cleaning
clean:
	@ $(RM) -r $(BUILD_DIR)

fclean: clean
	@ $(RM) $(NAME) ../$(NAME)
	@ $(RM) ../../include/my.h
	@ $(RM) ../../include/colors.h

.PHONY: clean fclean

re: fclean all

.PHONY: re

-include $(DEPS)
