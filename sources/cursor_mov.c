/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 03:53:16 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/26 19:09:07 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_pos_before_nl()
{
	int		len;
	int		i;

	i = g_info.strlen - g_info.cursor - 1;
	len = 0;
	while (--i && g_info.line[i] != '\n')
		len++;
	tputs(tgoto(g_info.cap.cm, len % g_info.col, g_info.crsr_row - 1),
			1, ft_putc);
}

void	ft_mv_left()
{
	if (g_info.crsr_col == 0)
	{
		if (g_info.line[g_info.strlen - g_info.cursor - 1] == '\n')
			tputs(tgoto(g_info.cap.cm, ft_getcol_fromstr(g_info.strlen - g_info.cursor - 1), g_info.crsr_row - 1), 1, ft_putc);
		else if (g_info.crsr_row > 0)
			tputs(tgoto(g_info.cap.cm, g_info.col - 1, g_info.crsr_row - 1),
					1, ft_putc);
		else
		{
			ft_scroll(1, 'R');
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

void	ft_mv_right()
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
			ft_scroll(1, 'F');
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

int		ft_reach_next_word(void)
{
	int		i;

	i = g_info.strlen - g_info.cursor;
	while (g_info.line[i] == ' ' && g_info.line[i])
	{
		i++;
		ft_mv_right();
	}
	while (g_info.line[i] && ft_isprint(g_info.line[i]) && g_info.line[i] != ' ')
	{
		ft_mv_right();
		i++;
	}
	return (i);
}

int		ft_reach_previous_word(void)
{
	int		i;

	i = g_info.strlen - g_info.cursor;
	if (i > 0)
	{
		ft_mv_left();
		while (--i && (g_info.line[i] == ' ' || !(g_info.line[i])))
		{
			ft_mv_left();
		}
		while (i > 0 && ft_isprint(g_info.line[i]) && g_info.line[i] != ' ')
		{
			ft_mv_left();
			i--;
		}
		if (g_info.line[i] == ' ')
		{
			ft_mv_right();
			i++;
		}
	}
	return (i);
}
