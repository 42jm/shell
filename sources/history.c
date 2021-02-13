/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:15:06 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/01 23:43:42 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	**ft_history_init(void)
{
	if (!(g_info.hist = (char **)ft_memalloc(sizeof(char **))))
		return (NULL);
	g_info.hist[0] = NULL;
	return (g_info.hist);
}

char	**ft_history_new(void)
{
	int		i;
	char	**hist;

	i = 0;
	while (g_info.hist[i])
		i++;
	if (!(g_info.line[0]) || (i > 1 && !ft_strcmp(g_info.line, g_info.hist[0])))
		return (g_info.hist);
	if (!(hist = (char **)ft_memalloc(sizeof(char **) * (i + 2))))
		return (NULL);
	hist[0] = ft_strdup(g_info.line);
	i = -1;
	while (g_info.hist[++i])
		hist[i + 1] = g_info.hist[i];
	hist[i + 1] = NULL;
	free(g_info.hist);
	return (g_info.hist = hist);
}

void	ft_history(char opt)
{
	ft_ctrl_a();
	ft_clean_after_cursor();
	if (g_info.hist_pos == -1)
	{
		free(g_info.temp);
		g_info.temp = ft_strdup(g_info.line);
	}
	free(g_info.line);
	if (opt == '+')
		(g_info.hist_pos)++;
	else if (opt == '-')
		(g_info.hist_pos)--;
	if (g_info.hist_pos == -1)
		g_info.line = ft_strdup(g_info.temp);
	else
		g_info.line = ft_strdup(g_info.hist[g_info.hist_pos]);
	g_info.strlen = ft_strlen(g_info.line);
	ft_putstr(g_info.line);
	ft_get_cursor_info();
	g_info.cursor = 0;
}
