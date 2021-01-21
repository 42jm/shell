/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:15:06 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/20 22:40:50 by quegonza         ###   ########.fr       */
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
	if (i > 1 && (!ft_strcmp(g_info.line, g_info.hist[0]) || !(g_info.line[0])))
		return (g_info.hist);
	if (!(hist = (char **)ft_memalloc(sizeof(char **) * (i + 2))))
		return (NULL);
	hist[0] = g_info.line;
	i = -1;
	while (g_info.hist[++i])
		hist[i + 1] = g_info.hist[i];
	hist[i + 1] = NULL;
	free(g_info.hist);
	g_info.hist = hist;
	return (hist);
}

/*
char	**ft_history_new(void)
{
	int		i;
	int		dbl;
	char	**hist;

	i = 0;
	dbl = 0;
	while (g_info.hist[i])
		i++;
	if (i > 1 && (!ft_strcmp(g_info.hist[0], g_info.hist[1])
						|| !(g_info.hist[0][0])))
		dbl = 1;
	if (!(hist = (char **)ft_memalloc(sizeof(char **) * (i + 2 - dbl))))
		return (NULL);
	if (!(hist[0] = (char *)ft_memalloc(sizeof(char *))))
		return (NULL);
	i = dbl > 0 ? 0 : -1;
	while (g_info.hist[++i])
		hist[i + 1 - dbl] = g_info.hist[i];
	hist[i + 1 - dbl] = NULL;
	if (dbl)
		free(g_info.hist[0]);
	free(g_info.hist);
	g_info.hist = hist;
	return (g_info.hist);
}
*/

void	ft_history(char opt)
{
	ft_ctrl_a();
	ft_erase_crsrline();
	if (g_info.cursor + g_info.crsr_col >= g_info.col)
	{
		tputs(tgoto(g_info.cap.cm, 0, g_info.crsr_row + 1), 1, ft_putc);
		tputs(g_info.cap.cd, g_info.row - g_info.crsr_row - 1, ft_putc);
		tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row),
					1, ft_putc);
	}
	if (!(g_info.hist_pos))
	{
		free(g_info.hist[0]);
		g_info.hist[0] = ft_strdup(g_info.line);
	}
	if (opt == '+')
		(g_info.hist_pos)++;
	else if (opt == '-')
		(g_info.hist_pos)--;
	g_info.strlen = ft_strlen(g_info.hist[g_info.hist_pos]);
	free(g_info.line);
	g_info.line = ft_strdup(g_info.hist[g_info.hist_pos]);
	ft_putstr(g_info.hist[g_info.hist_pos]);
	ft_input_init();
}

void	ft_free_tabzero(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_display_history(void)
{
	int	i;

	i = 0;
	while (g_info.hist[i])
	{
		ft_putstr("---> ");
		ft_putstr(g_info.hist[i]);
		ft_putchar('\n');
		i++;
	}
}
