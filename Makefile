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
CFLAGS += -iquote ./include

# ↓ Binaries
NAME := mysh
TEST_NAME := unit_tests
ASAN_NAME := asan
PROF_NAME := prof

# Libmy
LIBMY := lib/libmy.a
LDFLAGS := -L./$(dir $(LIBMY)) -lmy

# Source files
VPATH := src
SRC := minishell.c
SRC += clear.c
SRC += lexer.c
SRC += execute/execute.c
SRC += execute/cmd_path.c
SRC += execute/argv.c
SRC += env/env.c
SRC += env/envp.c
SRC += builtins/builtins.c
SRC += builtins/exit.c
SRC += builtins/env.c
SRC += builtins/cd.c

# Tests files
VPATH += tests
TEST_SRC := $(SRC)
TEST_SRC += test_working.c

SRC += main.c

# ↓ Objects
BUILD_DIR := .build
OBJ := $(SRC:%.c=$(BUILD_DIR)/source/%.o)
TEST_OBJ := $(TEST_SRC:%.c=$(BUILD_DIR)/tests/%.o)
ASAN_OBJ := $(SRC:%.c=$(BUILD_DIR)/asan/%.o)
PROF_OBJ := $(SRC:%.c=$(BUILD_DIR)/prof/%.o)

# ↓ Dependencies for headers
DEPS_FLAGS := -MMD -MP
DEPS := $(OBJ:.o=.d)
TEST_DEPS := $(TEST_OBJ:.o=.d)
ASAN_DEPS := $(ASAN_OBJ:.o=.d)
PROF_DEPS := $(PROF_OBJ:.o=.d)

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

# ↓ Compiling libmy
$(LIBMY):
	@ $(MAKE) -s -C $(dir $(LIBMY))/my

libmy: $(LIBMY)

.PHONY: libmy

# ↓ Compiling
$(BUILD_DIR)/source/%.o: %.c $(LIBMY)
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(NAME): $(LIBMY) $(OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS) || $(DIE)

.PHONY: $(NAME)

# ↓ Unit tests
$(BUILD_DIR)/tests/%.o: %.c $(LIBMY)
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

ifneq ($(NO_COV), 1)
$(TEST_NAME): CFLAGS += -g3 --coverage
endif
$(TEST_NAME): CFLAGS += -lcriterion
$(TEST_NAME): $(LIBMY) $(TEST_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(TEST_OBJ) $(CFLAGS) $(LDFLAGS) || $(DIE)

tests_run: fclean $(TEST_NAME)
	@-./$(TEST_NAME)

.PHONY: $(TEST_NAME) tests_run

# ↓ Asan
$(BUILD_DIR)/asan/%.o: %.c $(LIBMY)
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(ASAN_NAME): CFLAGS += -fsanitize=address,leak,undefined -g3
$(ASAN_NAME): CFLAGS += -D DEBUG_MODE
$(ASAN_NAME): $(LIBMY) $(ASAN_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(ASAN_OBJ) $(CFLAGS) $(LDFLAGS) || $(DIE)

.PHONY: $(ASAN_NAME)

# ↓ Profiler
$(BUILD_DIR)/prof/%.o: %.c $(LIBMY)
	@ mkdir -p $(dir $@)
	@ $(ECHO) "[${C_BOLD}${C_RED}CC${C_RESET}] $^"
	@ $(CC) -o $@ -c $< $(CFLAGS) $(DEPS_FLAGS) || $(DIE)

$(PROF_NAME): CFLAGS += -pg
$(PROF_NAME): $(LIBMY) $(PROF_OBJ)
	@ $(ECHO) "[${C_BOLD}${C_YELLOW}CC${C_RESET}] ${C_GREEN}$@${C_RESET}"
	@ $(CC) -o $@ $(PROF_OBJ) $(CFLAGS) $(LDFLAGS) || $(DIE)

.PHONY: $(PROF_NAME)

# ↓ Coverage
cov: GCOVR_FLAGS := --exclude bonus/
cov: GCOVR_FLAGS += --exclude tests/
cov:
	@ gcovr $(GCOVR_FLAGS)
	@ gcovr $(GCOVR_FLAGS) --branches

.PHONY: cov

# ↓ Cleaning
clean:
	@ $(RM) $(OBJ) $(TEST_OBJ) $(ASAN_OBJ)

fclean: clean
	@ $(RM) $(NAME) $(TEST_NAME) $(ASAN_NAME) $(PROF_NAME)
	@ $(RM) -r $(BUILD_DIR)
	@ $(MAKE) -s -C $(dir $(LIBMY))/my fclean

.PHONY: clean fclean

re: fclean
	@ $(MAKE) -s -C .

.PHONY: re

-include $(DEPS)
-include $(TEST_DEPS)
-include $(ASAN_DEPS)
-include $(PROF_DEPS)
