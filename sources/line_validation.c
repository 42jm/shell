/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:44:26 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/05 23:32:01 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_find_eof(char *eof, int i, int len)
{
	if (g_info.eof)
		i = g_info.eof;
	while (g_info.line[i])
	{
		if (i && !ft_strncmp(&(g_info.line[i]), eof, len)
			&& g_info.line[i - 1] == '\n' && g_info.line[i + len] == '\n')
		{
			g_info.eof = i;
			free(eof);
			return (1);
		}
		i++;
	}
	free(eof);
	return (0);
}

int 	ft_valid_hdoc(int i)
{
	char	*eof;
	char	*tmp;
	int		len;

	while (g_info.line[i] == ' ' || g_info.line[i] == '\t')
		i++;
	len = ft_stralen_unquoted(&(g_info.line[i]), "><&();| \t\n") - 1;
	if (!len)
		return (1);
	tmp = ft_memalloc(len + 1);
	if (!tmp)
		return (0);
	ft_strncpy(tmp, &(g_info.line[i]), len);
	eof = remove_quotes(tmp);
	free(tmp);
	len = ft_strlen(eof);
	i += len - 1;
	if (ft_find_eof(eof, i, len))
		return (1);
	return (0);
}

size_t	ft_quotationlen(char *s, char *quotes)
{
	size_t	len;
	char	quote;

	if (!s)
		return (0);
	quote = *s;
	if (!ft_strchr(quotes, quote))
		return (0);
	if (quote == '\\')
		return (2);
	len = 1;
	while (s[len])
	{
		if (quote == '"' && s[len] == '\\' && s[len + 1])
			len += 2;
		else if (s[len] == quote)
			return (len + 1);
		else
			len++;
	}
	return (0);
}

int 	ft_quote_hdoc(char chr, int *i)
{
	int		len;

	if ((chr == '\'' || chr == '\"') && !(g_info.eof))
	{
		len = ft_quotationlen(&(g_info.line[*i]), "\\'\"");
		if (!len || len == 1 || g_info.line[*i + len - 1] != chr)
			return (0);
		*i += len;
	}
	else if (g_info.line[*i] == '<' && g_info.line[*i + 1] == '<')
	{
		*i += 2;
		if (!ft_valid_hdoc(*i))
			return (0);
	}
	else
		*i += 1;
	return (1);
}

int 	ft_line_validation(void)
{
	int		i;

	if (g_info.exit)
		return (1);
	if (g_info.strlen && g_info.line[g_info.strlen - 1] == '\n')
	{
		i = 0;
		while (g_info.line[i])
		{
			if (g_info.line[i] == '\\' && g_info.line[i + 1])
				i += 2;
			else if (!ft_quote_hdoc(g_info.line[i], &i))
				return (0);
		}
		g_info.line[g_info.strlen - 1] = '\0';
		return (1);
	}
	return (0);
}
