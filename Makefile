# Colours
NO_COLOR = \033[0m
WAIT_COLOR = \033[1;33m
OK_COLOR = \033[1;32m
CLEAN_COLOR = \033[1;36m

# Compilation
NAME = 21sh
INC = -I includes -I libft/includes
LIB = -L libft/ -lft -lncurses
FLAGS = -Wall -Wextra -Werror -ggdb#-fsanitize=address

# Files
OBJ_DIR = objects/
SRC_DIR = sources/
SRC_NAME = main.c \
	astexec_assign.c \
	astexec_braces.c \
	astexec_pipe.c \
	astexec_redir.c \
	astexec_separ.c \
	astexec_simplecmd.c \
	ast_execute.c \
	ast_free.c \
	ast_lexer.c \
	astlex_len.c \
	astlex_op.c \
	astlex_token.c \
	astparse_andor.c \
	astparse_curly.c \
	astparse_parentheses.c \
	ast_parser.c \
	ast_put.c \
	astredir_aggregate.c \
	astredir_heredoc.c \
	astredir_local.c \
	astredir_simple.c \
	ast_to_strarr.c \
	bltn_cd.c \
	bltn_echo.c \
	bltn_envs.c \
	bltn_exit.c \
	cursor_info.c \
	cursor_mov.c \
	env.c \
	env_convert.c \
	env_get.c \
	env_new.c \
	env_put.c \
	error.c \
	exec_str_in_subshell.c \
	execute.c \
	expansion.c \
	expansion_op.c \
	expansion_param.c \
	expansion_remove.c \
	expansion_tilde.c \
	file_tests.c \
	ft_strcsplit_all.c \
	ft_strlen_unquoted.c \
	get_user_input.c \
	history.c \
	line_edition.c \
	line_validation.c \
	prompt.c \
	read.c \
	sighandlers.c \
	signals.c \
	size1_char_typing.c \
	size3_char_typing.c \
	start_up.c \
	termcap_tools.c \
	tests.c \
	usefull_scratch.c

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

# Rules
.PHONY: all clean fclean re libft

all: $(NAME)

$(NAME): Makefile libft/libft.a $(OBJ)
	@printf "\n$(WAIT_COLOR)$(NAME): linking\$(NO_COLOR)\n"
	@clang $(FLAGS) -o $(NAME) $(OBJ) $(INC) $(LIB)
	@echo "$(OK_COLOR)	+++ " $@ "   created +++	$(NO_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@clang $(FLAGS) -c $< -o $@ $(INC)
	@echo -n "$(WAIT_COLOR)+$(NO_COLOR)"

libft/libft.a:
	@make --quiet -C libft

clean:
	@make --quiet -C libft clean
	@rm -rf $(OBJ_DIR)
	@echo "$(CLEAN_COLOR)	--- $(NAME) object files deleted ---$(NO_COLOR)"

fclean:
	@make --quiet -C libft fclean
	@rm -rf $(OBJ_DIR)
	@echo "$(CLEAN_COLOR)	--- $(NAME) object files deleted ---$(NO_COLOR)"
	@rm -f $(NAME)
	@echo "$(CLEAN_COLOR)	--- $(NAME)  deleted ---		$(NO_COLOR)"

re:	fclean all
