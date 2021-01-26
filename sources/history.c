/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 23:15:06 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/26 19:58:02 by quegonza         ###   ########.fr       */
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
	ft_erase_crsrline();
	if (ft_getrow_fromstr(g_info.strlen) != g_info.crsr_row)
	{
		tputs(tgoto(g_info.cap.cm, 0, g_info.crsr_row + 1), 1, ft_putc);
		tputs(g_info.cap.cd, g_info.row - g_info.crsr_row - 1, ft_putc);
		tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row),
					1, ft_putc);
	}
	if (g_info.hist_pos == -1)
		g_info.temp = ft_strdup(g_info.line);
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
