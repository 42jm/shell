/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 05:44:26 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/23 15:40:58 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_find_eof(char *eof, int *j, int i, int len)
{
	while (g_info.line[++i])
	{
		if (!(ft_strncmp(&(g_info.line[i]), eof, len)))
		{
			free(eof);
			*j = i;
			return (1);
		}
	}
	free(eof);
	*j = i;
	return (0);
}

int 	ft_valid_hdoc(int *j)
{
	char	*eof;
	char	*tmp;
	int		len;
	int		i;

	i = *j;
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
	if (ft_find_eof(eof, j, i, len))
		return (1);
	return (0);
}

int 	ft_valid_quotes(void)
{
	int		i;
	int		len;
	char	chr;

	i = 0;
	while (g_info.line[i])
	{
		chr = g_info.line[i];
		if (chr == '\'' || chr == '\"')
		{
			len = quotationlen(&(g_info.line[i]), "\\'\"");
			if (!len || len == 1 || g_info.line[i + len - 1] != chr)
				return (0);
			i += len;
		}
		else if (g_info.line[i] == '<' && g_info.line[i + 1] == '<')
		{
			i += 2;
			if (!ft_valid_hdoc(&i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int 	ft_line_validation(void)
{
	if (g_info.exit)
		return (1);
	if (g_info.strlen && g_info.line[g_info.strlen - 1] == '\n')
	{
		if (!ft_valid_quotes())
			return (0);
		g_info.line[g_info.strlen - 1] = '\0';
		return (1);
	}
	return (0);
}
