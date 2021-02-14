/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:44:26 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/14 15:30:16 by quegonza         ###   ########.fr       */
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
	word = ft_memalloc(i + 1);
	if (!word)
		return (NULL);
	return (word = ft_strncpy(word, str, i));
}

int 	ft_valid_hdoc(int i)
{
	char	*eof;
	int		eoflen;

	i += 2;
	while (g_info.line[i] == ' ' || g_info.line[i] == '\t')
		i++;
	eof = ft_str_first_word(&(g_info.line[i]));
	eoflen = ft_strlen(eof);
	i += eoflen - 1;
	while (g_info.line[++i])
	{
		if (!(ft_strncmp(&(g_info.line[i]), eof, eoflen)))
		{
			free(eof);
			return (1);
		}
	}
	free(eof);
	return (0);
}

int 	ft_valid_quotes(void)
{
	int		i;

	i = -1;
	while (g_info.line[++i])
	{
		if (g_info.line[i] == '\'')
		{
			while (g_info.line[++i] != '\'')
				if (!g_info.line[i])
					return (0);
		}
		else if (g_info.line[i] == '\"')
		{
			while (g_info.line[++i] != '\"')
				if (!g_info.line[i])
					return (0);
		}
		else if (g_info.line[i] == '<' && g_info.line[i + 1] == '<')
			if (!ft_valid_hdoc(i))
				return (0);
	}
	return (1);
}

int 	ft_line_validation(void)
{
	if (g_info.exit)
	{
		g_info.exit = 0;
		return (1);
	}
	if (g_info.strlen && g_info.line[g_info.strlen - 1] == '\n')
	{
		if (!ft_valid_quotes())
			return (0);
		g_info.line[g_info.strlen - 1] = '\0';
		return (1);
	}
	return (0);
}
