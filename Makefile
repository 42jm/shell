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
			parse.c \
			parse_expand.c \
			env.c \
			execute.c \
			execute_helpers.c \
			error.c \
			bltn_echo.c \
			bltn_exit.c \
			bltn_cd.c \
			bltn_envs.c
SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

# Rules
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make --quiet -C libft
	@printf "$(NAME): linking\n"
	@clang $(FLAGS) -o $(NAME) $(OBJ) $(INC) $(LIB)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@printf "$(NAME): compiling $@\n"
	@mkdir -p $(OBJ_DIR)
	@clang $(FLAGS) -c $< -o $@ $(INC)

clean:
	@make --quiet -C libft clean
	@printf "$(NAME): removing objects\n"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make --quiet -C libft fclean
	@printf "$(NAME): removing $(NAME)\n"
	@rm -f $(NAME)

re:	fclean all
