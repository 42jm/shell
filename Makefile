# Compilation
NAME = 21sh
INC = -I includes -I libft/includes
LIB = -L libft/ -lft
FLAGS = -Wall -Wextra -Werror

# Files
OBJ_DIR = objects/
SRC_DIR = sources/
SRC_NAME = main.c \
			signals.c \
			prompt.c \
			read.c \
			ft_strcsplit_all.c \
			ft_strlen_unquoted.c \
			ast_to_strarr.c \
			ast_put.c \
			ast_free.c \
			ast_parser.c \
			astparse_andor.c \
			astlex_token.c \
			astlex_len.c \
			astlex_op.c \
			ast_lexer.c \
			astexec_simplecmd.c \
			astexec_assign.c \
			astexec_redir.c \
			astexec_separ.c \
			astexec_pipe.c \
			ast_execute.c \
			astredir_aggregate.c \
			astredir_heredoc.c \
			astredir_simple.c \
			astredir_local.c \
			expansion.c \
			expansion_param.c \
			expansion_tilde.c \
			env.c \
			env_convert.c \
			env_get.c \
			env_new.c \
			env_put.c \
			execute.c \
			file_tests.c \
			bltn_echo.c \
			bltn_exit.c \
			bltn_envs.c \
			bltn_cd.c \
			error.c
SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

# Rules
.PHONY: all clean fclean re libft

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@printf "$(NAME): linking\n"
	@clang $(FLAGS) -o $(NAME) $(OBJ) $(INC) $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(NAME): compiling $@\n"
	@mkdir -p $(OBJ_DIR)
	@clang $(FLAGS) -c $< -o $@ $(INC)

libft/libft.a:
	@make --quiet -C libft

clean:
	@make --quiet -C libft clean
	@printf "$(NAME): removing objects\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make --quiet -C libft fclean
	@printf "$(NAME): removing $(NAME)\n"
	@rm -f $(NAME)

re:	fclean all
