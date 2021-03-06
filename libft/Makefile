# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/12 09:27:03 by jmbomeyo          #+#    #+#              #
#    Updated: 2021/03/29 20:18:51 by quegonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#\/\/\/Colours
NO_COLOR = \033[0m
WAIT_COLOR = \033[1;33m
OK_COLOR = \033[1;32m
CLEAN_COLOR = \033[1;36m

NAME = libft.a
SRC = ft_atoi.c \
	   ft_atoi_strict.c \
	   ft_atollu.c \
	   ft_bzero.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isprint.c \
	   ft_itoa.c \
	   ft_itoa_base.c \
	   ft_lstadd.c \
	   ft_lstdel.c \
	   ft_lstdelone.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_lstnew.c \
	   ft_lstfree.c \
	   ft_lstdup.c \
	   ft_memalloc.c \
	   ft_memccpy.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memdel.c \
	   ft_memmove.c \
	   ft_memrchr.c \
	   ft_memset.c \
	   ft_putchar.c \
	   ft_putchar_fd.c \
	   ft_putchar_binary.c \
	   ft_putchar_binary_fd.c \
	   ft_putendl.c \
	   ft_putendl_fd.c \
	   ft_putnbr.c \
	   ft_putnbr_fd.c \
	   ft_putstr.c \
	   ft_putstr_fd.c \
	   ft_putstr_lower.c \
	   ft_putstr_upper.c \
	   ft_putusage.c \
	   ft_strcat.c \
	   ft_strchr.c \
	   ft_strclr.c \
	   ft_strcmp.c \
	   ft_strcpy.c \
	   ft_strdel.c \
	   ft_strdup.c \
	   ft_strequ.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strcjoin.c \
	   ft_strlast.c \
	   ft_strlcat.c \
	   ft_strlen.c \
	   ft_strlen_arr.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strncat.c \
	   ft_strncmp.c \
	   ft_strncpy.c \
	   ft_strndup.c \
	   ft_strnequ.c \
	   ft_strnew.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strcsplit.c \
	   ft_strnsplit.c \
	   ft_strsplit.c \
	   ft_strstrsplit.c \
	   ft_strstr.c \
	   ft_strsub.c \
	   ft_strtrim.c \
	   ft_strjoin_arr.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_lstappend.c \
	   ft_lstpop.c \
	   ft_lstlen.c \
	   ft_lstlen_upto.c \
	   ft_lstprint.c \
	   ft_putnstr.c \
	   ft_strcdup.c \
	   ft_strclen.c \
	   ft_putstr_arr.c \
	   ft_strlower.c \
	   ft_strupper.c \
	   ft_strcmp_ci.c \
	   ft_strcrop.c \
	   ft_strdrop.c \
	   ft_strdrop_inplace.c \
	   ft_strninsert.c \
	   ft_strreplace.c \
	   ft_ltoa.c \
	   ft_pow.c \
	   ft_read.c \
	   ft_puthex.c \
	   ft_puthex_fd.c \
	   ft_strhex.c \
	   ft_putjoin.c \
	   ft_intarr.c \
	   ft_lutoa.c \
	   ft_strcnew.c \
	   endian_toggle.c \
	   free_strarr.c \
	   free_strarr_all.c \
	   ft_arrint.c \
	   ft_arrstr.c \
	   ft_arrnstr.c \
	   ft_arrstr_id.c \
	   ft_strdup_arr.c \
	   pr_putstr_fd.c \
	   pr_putendl_fd.c \
	   pr_strlen.c \
	   ft_strarr_to_lst.c \
	   ft_lst_to_strarr.c \
	   ft_lstfind_head.c \
	   ft_opt.c
INC_DIR = includes/
OBJ_DIR = objects/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(OK_COLOR)\n ++ libft archived ++ $(NO_COLOR)"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@clang -Wall -Wextra -Werror -c $< -o $@ -I $(INC_DIR)
	@printf "$(WAIT_COLOR)+$(NO_COLOR)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(CLEAN_COLOR) -- libft .o files deleted --$(NO_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(CLEAN_COLOR) -- libft.a deleted --$(NO_COLOR)"

re: fclean all
