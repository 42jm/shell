/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:49:27 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 11:50:27 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_COMPLETION_H
# define AUTO_COMPLETION_H

# include <sys/types.h>
# include <dirent.h>

# define C_UP				"up"
# define DOWN				"do"
# define LEFT				"le"
# define RIGHT				"nd"
# define SAVE				"sc"
# define RESET_C			"rc"
# define SCROLL_DOWN		"sr"
# define SCROLL_UP			"sf"
# define CLEAR_FROM_CURR	"cd"
# define DEL_LINE			"dl"

# define B_BLUE				"\033[46m"
# define BLUE				"\033[38;5;61m"
# define GREEN				"\033[38;5;29m"
# define CYAN				"\033[38;5;50m"
# define RED 	    		"\033[1;31m"
# define COLOR_RESET    	"\033[0m"

extern t_list	*g_choice;

char	*auto_completion(char *line);

/*
**	Parsing Contextualization
*/

char	*get_current_word(char *line, int i);
char	*complete_word(char *line, char **word, char *insert, int insert_idx);
int		is_first_word(char *line);

/*
** Directory
*/
int		is_directory(char *word, int is_path, int *insert_idx);

/*
**	Display
*/

void	print_completion_choice(int is_var);

/*
** Fill Choice
*/
int		fill_choice(char *line, char *word, int *insert_idx);

/*
**	Handle Choice
*/

t_list	*make_choice(const void *content);
int		get_longest_choice_len(void);
void	free_choice(void);

/*
**	Utils
*/

int		strchri(char *str, char c);
int		is_whitespace(char c);
char	**get_shell_variable(t_list *entry);

#endif
