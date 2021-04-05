/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:10:12 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/05 22:28:28 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_line_rest(int rest, char *new, char *line)
{
	int		nb;
	int		crsr_col;
	int		crsr_row;

	ft_putstr(&line[g_info.strlen - rest + 1]);
	crsr_row = g_info.crsr_row;
	crsr_col = g_info.crsr_col;
	if (new)
	{
		ft_get_cursor_info();
		if (g_info.crsr_row == g_info.row - 1
			&& g_info.crsr_col == g_info.col - 1)
		{
			ft_putchar('\n');
			(g_info.crsr_row)--;
			crsr_row--;
		}
		nb = g_info.strlen - g_info.cursor;
		while (--rest)
			new[++nb] = line[g_info.strlen - rest];
	}
	tputs(tgoto(g_info.cap.cm, crsr_col, crsr_row), 1, ft_putc);
	ft_get_cursor_pos();
}

char	*ft_insert_char(char *line, char chr)
{
	char	*new;
	int		i;
	int		lim;

	new = (char *)ft_memalloc(g_info.strlen + 2);
	if (!new)
		return (NULL);
	i = -1;
	lim = g_info.strlen - g_info.cursor;
	while (++i < lim)
		new[i] = line[i];
	new[i] = chr;
	ft_putchar(chr);
	if (g_info.crsr_col == g_info.col - 1 && chr != '\n')
		ft_putchar('\n');
	ft_get_cursor_pos();
	if (g_info.cursor)
		ft_line_rest(g_info.cursor + 1, new, line);
	free(line);
	g_info.strlen += 1;
	return (new);
}

char	*ft_suppr_char(char *line)
{
	char	*new;
	int		i;
	int		lim;

	new = (char *)ft_memalloc(g_info.strlen);
	if (!new)
		return (NULL);
	i = -1;
	lim = g_info.strlen - g_info.cursor;
	while (++i < lim)
		new[i] = line[i];
	lim = g_info.cursor;
	ft_clean_after_cursor();
	ft_line_rest(lim, NULL, line);
	while (--lim)
		new[i++] = line[g_info.strlen - lim];
	free(line);
	g_info.strlen -= 1;
	g_info.cursor -= 1;
	return (new);
}

char	*ft_del_char(char *line)
{
	char	*new;
	int		i;
	int		lim;

	new = (char *)ft_memalloc(g_info.strlen);
	if (!new)
		return (NULL);
	i = -1;
	lim = g_info.strlen - g_info.cursor - 1;
	while (++i < lim)
		new[i] = line[i];
	ft_mv_left();
	ft_clean_after_cursor();
	g_info.cursor -= 1;
	if (g_info.cursor)
	{
		lim = g_info.cursor + 1;
		ft_line_rest(lim, NULL, line);
		while (--lim)
			new[i++] = line[g_info.strlen - lim];
	}
	free(line);
	g_info.strlen -= 1;
	return (new);
}

void	ft_clean_after_cursor(void)
{
	int		i;
	int		maxcol;

	ft_get_cursor_info();
	i = g_info.crsr_col - 1;
	maxcol = g_info.col;
	while (++i < maxcol)
		ft_putchar(' ');
	if (ft_getrow_fromstr(g_info.strlen) != g_info.crsr_row)
	{
		tputs(tgoto(g_info.cap.cm, 0, g_info.crsr_row + 1), 1, ft_putc);
		tputs(g_info.cap.cd, g_info.row - g_info.crsr_row - 1, ft_putc);
	}
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
}
