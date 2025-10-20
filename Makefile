# --- Names ---
NAME		= libasm.a
TEST_NAME	= tests_bin

# --- OS Detection for Portability ---
UNAME_S		:= $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	AS_FORMAT = -f macho64
else
	AS_FORMAT = -f elf64
endif

# --- Tools & Flags ---
AS		= nasm
ASFLAGS		= $(AS_FORMAT)
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
AR		= ar
ARFLAGS		= rcs
VALGRIND	= valgrind
VFLAGS		= --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

# --- Directories ---
SRC_DIR		= src
TEST_DIR	= test
BUILD_DIR	= .build
INCLUDE_DIR	= include

# --- Source Files ---
ASM_SRCS	= $(wildcard $(SRC_DIR)/*.s)
TEST_SRCS	= $(wildcard $(TEST_DIR)/*.c)

# --- Object Files (with isolated paths) ---
OBJS		= $(ASM_SRCS:$(SRC_DIR)/%.s=$(BUILD_DIR)/src/%.o)
TEST_OBJS	= $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/test/%.o)

# --- Commands ---
RM		= rm -rf

# --- Main Rules ---
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^

# Rule to run the tests normally for quick checks
tests: $(TEST_NAME)
	@./$(TEST_NAME)

# Rule to run tests under Valgrind for memory leak and error checking
check: $(TEST_NAME)
	@$(VALGRIND) $(VFLAGS) ./$(TEST_NAME)

# --- Test Executable Rule ---
$(TEST_NAME): $(TEST_OBJS) $(NAME)
	@$(CC) $(CFLAGS) $(TEST_OBJS) -L. -lasm -o $(TEST_NAME)

# --- Compilation Pattern Rules ---
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(@D)
	@$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# --- Cleaning Rules ---
clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all tests check clean fclean re
