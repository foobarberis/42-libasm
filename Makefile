#*******************************  VARIABLES  **********************************#

NAME			=	libasm.a
TEST_NAME		=	tests_bin

# --------------- FILES --------------- #

LIST_ASM_SRC		=	\
						ft_atoi_base.s			\
						ft_create_elem.s		\
						ft_list.s				\
						ft_list_push_front.s	\
						ft_list_remove_if.s		\
						ft_list_size.s			\
						ft_list_sort.s			\
						ft_read.s				\
						ft_strcmp.s				\
						ft_strcpy.s				\
						ft_strdup.s				\
						ft_strlen.s				\
						ft_write.s

LIST_TEST_SRC		=	\
						ft_atoi_base.c			\
						ft_create_elem.c		\
						ft_list_push_front.c	\
						ft_list_remove_if.c		\
						ft_list_size.c			\
						ft_list_sort.c			\
						ft_read.c				\
						ft_strcmp.c				\
						ft_strcpy.c				\
						ft_strdup.c				\
						ft_strlen.c				\
						ft_write.c				\
						main.c					\
						utils.c

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_SRC 		=	src/
DIR_INCLUDE		=	include/
DIR_TEST		=	test/
DIR_LIB			=	lib/
DIR_UTEST		=	$(DIR_LIB)utest/

# ------------- SHORTCUTS ------------- #

OBJ				=	$(patsubst %.s, $(DIR_BUILD)%.o, $(SRC))
DEP				=	$(patsubst %.s, $(DIR_BUILD)%.d, $(SRC))
SRC				=	$(addprefix $(DIR_SRC), $(LIST_ASM_SRC))
TEST_SRC		=	$(addprefix $(DIR_TEST), $(LIST_TEST_SRC))
TEST_DEP		=	$(patsubst %.c, $(DIR_BUILD)%.d, $(TEST_SRC))
TEST_OBJ		=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST_SRC))
UTEST_INCLUDE	=	$(DIR_UTEST)

# ------------ COMPILATION ------------ #

AS				=	nasm
ASFLAGS			=	-f elf64 -I $(DIR_SRC)

CFLAGS			=	-Wall -Wextra -Werror

DEP_FLAGS		=	-MMD -MP

ARFLAGS			=	rcs

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

#***********************************  RULES  **********************************#


.PHONY: all
all:			$(NAME)

.PHONY: tests
tests: $(TEST_NAME)
				valgrind ./$(TEST_NAME)

$(TEST_NAME):	$(TEST_OBJ) $(NAME)
				$(CC) $(CFLAGS) $(TEST_OBJ) -L. -l:$(NAME) -o $(TEST_NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(OBJ)
				$(AR) $(ARFLAGS) $(NAME) $(OBJ)

# ---------- COMPILED RULES ----------- #

-include $(DEP)
$(DIR_BUILD)%.o: %.s
				mkdir -p $(shell dirname $@)
				$(AS) $(ASFLAGS) -MD $(@:.o=.d) $< -o $@

-include $(TEST_DEP)
$(DIR_BUILD)%.o: %.c
				mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) $(DEP_FLAGS) -c $< -o $@ -I $(DIR_INCLUDE) -I $(UTEST_INCLUDE)

.PHONY: clean
clean:
				$(RM) $(DIR_BUILD)

.PHONY: fclean
fclean: clean
				$(RM) $(NAME)
				$(RM) $(TEST_NAME)

.PHONY: re
re:				fclean
				$(MAKE) all

.PHONY: check-format
check-format:
				clang-format -style=file $(TEST_SRC) -n --Werror

.PHONY: format
format:
				clang-format -style=file $(TEST_SRC) -i
