# --- Names ---
NAME		= libasm.a
TEST_NAME	= tests_bin

# --- Tools & Flags ---
AS		= nasm
ASFLAGS	= -f elf64
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar
ARFLAGS	= rcs

# --- Directories ---
SRC_DIR		= src
TEST_DIR	= test
BUILD_DIR	= .build
INCLUDE_DIR	= include

# --- Source Files ---
ASM_SRCS	= $(wildcard $(SRC_DIR)/*.s)
TEST_SRCS	= $(wildcard $(TEST_DIR)/*.c)

# --- Object Files ---
# Create object file paths inside the build directory, mirroring the source structure
OBJS		= $(ASM_SRCS:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)
TEST_OBJS	= $(TEST_SRCS:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

# --- Commands ---
RM		= rm -rf

# --- Main Rules ---
all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^

tests: $(TEST_NAME)
	@./$(TEST_NAME)

# --- Test Executable Rule ---
$(TEST_NAME): $(TEST_OBJS) $(NAME)
	@$(CC) $(CFLAGS) $(TEST_OBJS) -L. -lasm -o $(TEST_NAME)

# --- Compilation Pattern Rules ---
# Rule to compile .s files from src/ into .o files in .build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(BUILD_DIR)
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to compile .c files from test/ into .o files in .build/
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# --- Cleaning Rules ---
clean:
	@$(RM) $(BUILD_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(TEST_NAME)

re: fclean all

.PHONY: all tests clean fclean re
