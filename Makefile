# Colours
NO_COLOR = \033[0m
WAIT_COLOR = \033[1;33m
OK_COLOR = \033[1;32m
CLEAN_COLOR = \033[1;36m

# Compilation
NAME = 42sh
INC = -I includes -I libft/includes
LIB = -L libft/ -lft -lncurses
FLAGS = -Wall -Wextra -Werror

# Files
OBJ_DIR = objects/
SRC_DIR = sources/
SRC_NAME = main.c \
	astexec_args.c \
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
	astparse_heredoc.c \
	astparse_parentheses.c \
	ast_parser.c \
	ast_put.c \
	astredir_aggregate.c \
	astredir_heredoc.c \
	astredir_local.c \
	astredir_simple.c \
	ast_to_strarr.c \
	bashvar.c \
	bltn_alias.c \
	bltn_unalias.c \
	bltn_cd.c \
	bltn_echo.c \
	bltn_envs.c \
	bltn_exit.c \
	bltn_jobs.c \
	bltn_pwd.c \
	bltn_setenvs.c \
	bltn_type.c \
	clear_dots.c \
	cursor_info.c \
	cursor_mov.c \
	cursor_pos_fromstr.c \
	copy_paste.c \
	env.c \
	env_convert.c \
	env_get.c \
	env_new.c \
	env_put.c \
	error.c \
	exec_str_in_subshell.c \
	execute.c \
	expansion.c \
	expansion_alias.c \
	expansion_op.c \
	expansion_param.c \
	expansion_remove.c \
	expansion_str.c \
	expansion_tilde.c \
	file_check.c \
	file_tests.c \
	ft_strcsplit_all.c \
	ft_strlen_unquoted.c \
	get_path.c \
	get_user_input.c \
	history.c \
	line_edition.c \
	line_validation.c \
	list_matching.c \
	options.c \
	prompt.c \
	read.c \
	resolve_path.c \
	sh_neg.c \
	sighandlers.c \
	signals.c \
	sig_int2str.c \
	size1_char_typing.c \
	size2_char_typing.c \
	size3_char_typing.c \
	start_up.c \
	tool_fcts.c \
	usefull_scratch.c \
	job_ast2str.c \
	job_ast2str_op.c \
	job_ast2str_get.c \
	job_init_shell.c \
	job_start_new.c \
	job_notifs.c \
	job_wait.c \
	job_launch.c \
	job_gets.c \
	job_cleanup.c \
	job_update.c \
	job_blueprint.c \
	job_free.c \
	job_puts.c \
	sig_get_core_signals.c \
	sig_get_ignored_signals.c \
	sig_get_term_signals.c \
	sig_dfl_signals_for_sub_process.c \
	sig_set_up_action_for_given_signals.c \
	sig_set_up_shell_signals.c	\
	is_whitespace.c	\
	strchri.c \
	completion_choice.c \
	completion_context.c \
	completion_directory.c \
	completion_display.c \
	completion_fill_choice.c \
	auto_completion.c	\
	completion_get_shell_variable.c

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

# Rules
.PHONY: all clean fclean re libft

all: $(NAME)

$(NAME): Makefile libft/libft.a $(OBJ) includes/quegonza.h includes/header_42sh.h includes/signals_42sh.h includes/auto_completion.h
	@printf "\n$(WAIT_COLOR)$(NAME): linking\$(NO_COLOR)\n"
	@clang -g3 $(FLAGS) -o $(NAME) $(OBJ) $(INC) $(LIB)
	@echo "$(OK_COLOR)	+++ " $@ "   created +++	$(NO_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@clang -g3 $(FLAGS) -c $< -o $@ $(INC)
	@printf "$(WAIT_COLOR)+$(NO_COLOR)"

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
