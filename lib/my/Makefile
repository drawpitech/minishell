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
SRC :=

SRC += std/convert_base.c
SRC += std/get_color.c
SRC += std/malloc.c
SRC += std/my_nbr_len.c
SRC += std/qsort.c
SRC += std/return_err.c
SRC += std/swap.c

SRC += string/get_fullpath.c
SRC += string/mem.c
SRC += string/my_nbr_to_base.c
SRC += string/my_show_word_array.c
SRC += string/my_showmem.c
SRC += string/my_showstr.c
SRC += string/my_str_join.c
SRC += string/my_str_startswith.c
SRC += string/my_strcat.c
SRC += string/my_strcmp.c
SRC += string/my_strcpy.c
SRC += string/my_strdup.c
SRC += string/my_strlen.c
SRC += string/my_strpbrk.c
SRC += string/my_strstr.c
SRC += string/reverse.c
SRC += string/str_identify.c
SRC += string/str_to_int.c
SRC += string/strcases.c
SRC += string/write_number.c

SRC += math/my_is_prime.c
SRC += math/my_pow.c
SRC += math/my_sqrt.c

SRC += io/my_printf/convertors/char.c
SRC += io/my_printf/convertors/float.c
SRC += io/my_printf/convertors/int.c
SRC += io/my_printf/convertors/len.c
SRC += io/my_printf/convertors/ptr.c
SRC += io/my_printf/convertors/str.c
SRC += io/my_printf/convertors/unsigned.c
SRC += io/my_printf/families/asprintf.c
SRC += io/my_printf/families/dprintf.c
SRC += io/my_printf/families/printf.c
SRC += io/my_printf/families/sprintf.c
SRC += io/my_printf/flag_parser.c
SRC += io/my_printf/flag_utils.c
SRC += io/my_putchar.c
SRC += io/my_putstr.c

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

# ↓ Cleaning
clean:
	@ $(RM) -r $(BUILD_DIR)

fclean: clean
	@ $(RM) $(NAME) ../$(NAME)

.PHONY: clean fclean

re: fclean all

.PHONY: re

-include $(DEPS)
