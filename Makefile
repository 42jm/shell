# Compilation
NAME = 21sh
INC = -I includes -I libft/includes
LIB = -L libft/ -lft
FLAGS = -Wall -Wextra -Werror

# Files
OBJ_DIR = objects/
SRC_DIR = sources/
SRC_NAME = main.c \
			prompt.c \
			read.c \
			ft_strcsplit_all.c \
			ft_strlen_unquoted.c \
			ast_to_strarr.c \
			ast_put.c \
			ast_free.c \
			ast_parser.c \
			ast_lexer.c \
			astlex_op.c \
			ast_execute.c \
			astexec_redir.c \
			astexec_simplecmd.c \
			astexec_separ.c \
			astexec_pipe.c \
			word_expansion.c \
			env.c \
			execute.c \
			file_tests.c \
			error.c \
			bltn_echo.c \
			bltn_exit.c \
			bltn_cd.c \
			bltn_envs.c
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
