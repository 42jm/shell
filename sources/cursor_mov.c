/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 03:53:16 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/07 09:14:57 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_mv_left(void)
{
	if (g_info.crsr_col == 0)
	{
		if (g_info.line[g_info.strlen - g_info.cursor - 1] == '\n')
			tputs(tgoto(g_info.cap.cm, ft_getcol_fromstr(g_info.strlen \
				- g_info.cursor - 1), g_info.crsr_row - 1), 1, ft_putc);
		else if (g_info.crsr_row > 0)
			tputs(tgoto(g_info.cap.cm, g_info.col - 1, g_info.crsr_row - 1),
				1, ft_putc);
		else
		{
			tputs(tgetstr("sr", NULL), g_info.row, ft_putc);
			tputs(tgoto(g_info.cap.cm, g_info.col - 1, g_info.crsr_row),
				1, ft_putc);
		}
	}
	else
	{
		tputs(tgoto(g_info.cap.cm, g_info.crsr_col - 1, g_info.crsr_row),
			1, ft_putc);
	}
	ft_get_cursor_info();
	(g_info.cursor)++;
}

void	ft_mv_right(void)
{
	if (g_info.line[g_info.strlen - g_info.cursor] == '\n')
		tputs(tgoto(g_info.cap.cm, 0, g_info.crsr_row + 1),
			1, ft_putc);
	else if (g_info.crsr_col == g_info.col - 1)
	{
		if (g_info.crsr_row < g_info.row - 1)
			tputs(tgoto(g_info.cap.cm, 0, g_info.crsr_row + 1),
				1, ft_putc);
		else
		{
			tputs(tgetstr("sf", NULL), g_info.row, ft_putc);
			tputs(tgoto(g_info.cap.cm, 0, g_info.crsr_row),
				1, ft_putc);
		}
	}
	else
	{
		tputs(tgoto(g_info.cap.cm, g_info.crsr_col + 1, g_info.crsr_row),
			1, ft_putc);
	}
	ft_get_cursor_info();
	(g_info.cursor)--;
}

void	ft_move_cursor(char side, int nb)
{
	if (nb > 0)
	{
		if (side == 'L')
			while (nb--)
				ft_mv_left();
		else if (side == 'R')
			while (nb--)
				ft_mv_right();
	}
}

int 	ft_reach_next_word(void)
{
	int	i;
	int	nb;

	ft_get_cursor_pos();
	i = g_info.strlen - g_info.cursor;
	nb = i;
	while (g_info.line[i] && !ft_isalnum(g_info.line[i]))
		i++;
	while (g_info.line[i] && ft_isalnum(g_info.line[i]))
		i++;
	g_info.crsr_row = ft_getrow_fromstr(i);
	g_info.crsr_col = ft_getcol_fromstr(i);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	nb = i - nb;
	g_info.cursor -= nb;
	if (g_info.cursor < 0)
		g_info.cursor = 0;
	return (i);
}

int 	ft_reach_previous_word(void)
{
	int	i;
	int	nb;

	i = g_info.strlen - g_info.cursor;
	if (i > 0)
	{
		ft_get_cursor_pos();
		nb = i;
		while (--i && !ft_isalnum(g_info.line[i]))
			;
		if (i)
		{
			while (i && ft_isalnum(g_info.line[i]))
				i--;
			if (!ft_isalnum(g_info.line[i]))
				i++;
		}
		g_info.crsr_row = ft_getrow_fromstr(i);
		g_info.crsr_col = ft_getcol_fromstr(i);
		tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row),
			1, ft_putc);
		nb = nb - i;
		g_info.cursor += nb;
	}
	return (i);
}
