/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:44:26 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/22 05:49:49 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_str_first_word(char *str)
{
	char	*word;
	int		i;

	i = 0;
	while (ft_isprint(str[i]))
		i++;
	if (!(word = ft_memalloc(i + 1)))
		return (NULL);
	return (word = ft_strncpy(word, str, i));
}

int		ft_valid_hdoc(int i)
{
	char 	*eof;

	i += 2;
	while (g_info.line[i] == ' ' || g_info.line[i] == '\t')
		i++;
	eof = ft_str_first_word(&(g_info.line[i]));
	i += ft_strlen(eof) - 1;
	while (g_info.line[++i])
		if (!(ft_strncmp(&(g_info.line[i]), eof, ft_strlen(eof))))
		{
			free(eof);
			return (1);
		}
	free(eof);
	return (0);
}

int		ft_valid_quotes()
{
	int		i;

	i = -1;
	while (g_info.line[++i])
	{
		if (g_info.line[i] == '\'')
			while (g_info.line[++i] != '\'')
			{
				if (!g_info.line[i])
					return (0);
			}
		else if (g_info.line[i] == '\"')
			while (g_info.line[++i] != '\"')
			{
				if (!g_info.line[i])
					return (0);
			}
		else if (g_info.line[i] == '<' && g_info.line[i + 1] == '<')
			if (!ft_valid_hdoc(i))
				return (0);
	}
	return (1);
}

int		ft_line_validation()
{
	if (g_info.strlen && g_info.line[g_info.strlen - 1] == '\n')
	{
		if (!ft_valid_quotes())
			return (0);
		g_info.line[g_info.strlen - 1] = '\0';
		return (1);
	}
	return (0);
}
