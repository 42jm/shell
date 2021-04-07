/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_context.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylemair <cylemair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 21:31:09 by cylemair          #+#    #+#             */
/*   Updated: 2021/04/07 10:51:03 by cylemair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

static int	is_separator(char c)
{
	if (c == '|' || c == ';' || c == '&')
		return (true);
	return (false);
}

int	is_first_word(char *line)
{
	int	i;

	i = g_info.strlen - g_info.cursor;
	i--;
	while (i > 0 && !is_whitespace(line[i]) && !is_separator(line[i]))
		i--;
	if (i == 0 || !is_whitespace(line[i])
		|| (is_separator(line[i]) && i != g_info.strlen - g_info.cursor))
		return (true);
	while (i >= 0 && is_whitespace(line[i]))
		i--;
	if (i < 0 || is_separator(line[i]))
		return (true);
	return (false);
}

char	*complete_word(char *line, char **word, char *insert, int insert_idx)
{
	char	*completed_word;

	if ((*word)[0] == '$')
		insert_idx--;
	while (insert[insert_idx]
		&& line[g_info.strlen - g_info.cursor] == insert[insert_idx])
	{
		ft_mv_right();
		insert_idx++;
	}
	completed_word = ft_strjoin(*word, &insert[insert_idx]);
	ft_strdel(word);
	*word = completed_word;
	while (insert[insert_idx])
	{
		line = ft_insert_char(line, insert[insert_idx]);
		insert_idx++;
	}
	return (line);
}

char	*get_current_word(char *line, int i)
{
	char			*ret;
	int				start;
	int				end;

	ft_get_cursor_info();
	end = g_info.strlen - g_info.cursor;
	start = end - 1;
	while (line && start && start - 1 >= 0 && !is_whitespace(line[start - 1])
		&& !is_separator(line[start - 1]))
		start--;
	ret = malloc(sizeof(char) * (end - start) + 1);
	if (!ret)
		return (NULL);
	while (start + i < end)
	{
		if (line[start + i] == '\'' || line[start + i] == '\"')
			start++;
		else
		{
			ret[i] = line[start + i];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}
