NAME = minishell
INC = -I includes -I libft/includes
LIB = -L libft/ -lft
FLAGS = -Wall -Wextra -Werror
SRC_DIR = sources/
SRC_NAME = main.c \
			prompt.c \
			read.c \
			parse.c \
			parse_expand.c \
			execute.c \
			execute_helpers.c \
			error.c \
			env.c \
			builtin_echo.c \
			builtin_exit.c \
			builtin_cd.c \
			builtin_envs.c

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(SRC_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft re
	@printf "[$(NAME)] creating objects\n"
	@clang $(FLAGS) -c $(SRC) $(INC)
	@printf "[$(NAME)] creating $(NAME)\n"
	@clang $(FLAGS) -o $(NAME) $(OBJ) $(INC) $(LIB)

clean:
	@make -C libft clean
	@printf "[$(NAME)] removing objects\n"
	@rm -f $(OBJ)

fclean: clean
	@make -C libft fclean
	@printf "[$(NAME)] removing $(NAME)\n"
	@rm -f $(NAME)

re:	fclean all
