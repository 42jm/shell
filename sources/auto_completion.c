/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:43:09 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 11:50:07 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

t_list	*g_choice;

static void	find_shellvar(char *word)
{
	char	**array;
	char	*tmp;
	int		i;
	int		word_idx;

	array = get_shell_variable(g_envlst);
	i = 0;
	word_idx = 1;
	if (word[1] == '{')
		word_idx++;
	while (array && array[i])
	{
		if (ft_strnequ(array[i], word + word_idx, ft_strlen(word + word_idx)))
		{
			tmp = ft_strndup(array[i], strchri(array[i], '='));
			g_choice = make_choice(tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	free_strarr_all(array);
}

static int	is_envar(char *word)
{
	if (word[0] == '$')
	{
		find_shellvar(word);
		return (true);
	}
	return (false);
}

static char	*handle_single_choice(char *line, char **word,
		int insert_idx, int dir)
{
	struct stat	sb;

	line = complete_word(line, word, g_choice->content, insert_idx);
	if (dir && lstat(*word, &sb) == -1)
	{
		ft_putstr("lstat: error: ");
		ft_putstr(*word);
	}
	else if (dir)
	{
		if (sb.st_mode && S_ISDIR(sb.st_mode))
		{
			if (line[g_info.strlen - g_info.cursor] == '/')
				ft_mv_right();
			else
				line = ft_insert_char(line, '/');
		}
	}
	return (line);
}

static char	*handle_var_single_choice(char *line, char **word, int insert_idx)
{
	char	*insert;

	if ((*word)[1] == '{')
	{
		insert = ft_strjoin(g_choice->content, "}");
		insert_idx--;
	}
	else
		insert = ft_strdup(g_choice->content);
	line = complete_word(line, word, insert, insert_idx);
	ft_strdel(&insert);
	return (line);
}

char	*auto_completion(char *line)
{
	char	*word;
	int		insert_idx;
	int		dir;
	int		var;

	dir = 0;
	if (line && ft_strlen(line))
	{
		word = get_current_word(line, 0);
		insert_idx = ft_strlen(word);
		var = is_envar(word);
		if (!var)
			dir = fill_choice(line, word, &insert_idx);
		if (g_choice && ft_lstlen(&g_choice) > 1 && line)
			print_completion_choice(var);
		else if (g_choice && ft_lstlen(&g_choice) == 1 && var)
			line = handle_var_single_choice(line, &word, insert_idx);
		else if (g_choice && ft_lstlen(&g_choice) == 1)
			line = handle_single_choice(line, &word, insert_idx, dir);
		ft_strdel(&word);
		free_choice();
	}
	return (line);
}
