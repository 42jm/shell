/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:16:23 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/09 21:14:31 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

/*
**FT_GET_CURSOR_POS():
**Requests cursor position to terminal with an XTerm Control Sequence on fd 1
**Terminal response has the form ^[42;1R
**symbol '^' stands for ESC code 27 (other symbols stand for their ASCII value)
**'42' would be the row where the cursor is on and '1' the (first) column
*/

void	ft_get_cursor_pos(void)
{
	int		i;
	char	buf[15];

	write(1, "\033[6n", 4);
	ft_bzero(buf, 15);
	if (read(1, buf, 14) == -1)
		return ;
	i = -1;
	while (buf[++i])
		if (buf[i] >= 48 && buf[i] <= 57)
		{
			g_info.crsr_row = ft_atoi(&buf[i]) - 1;
			while (buf[i] != ';')
				i++;
			g_info.crsr_col = ft_atoi(&buf[i + 1]) - 1;
			break ;
		}
}

void	ft_get_term_size(void)
{
	struct winsize ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	g_info.col = ws.ws_col;
	g_info.row = ws.ws_row;
}

void	ft_get_cursor_info(void)
{
	ft_get_term_size();
	ft_get_cursor_pos();
}

int		ft_getcol_fromstr(int cursor)
{
	int		i;
	int		col;

	i = g_info.strlen - g_info.cursor;
	col = g_info.crsr_col;
	while (i > cursor)
	{
		i--;
		if (g_info.line[i] == '\n')
			col = ft_line_len(i) % g_info.col;
		else if (!col)
			col = g_info.col - 1;
		else
			col--;
	}
	while (i < cursor)
	{
		if (g_info.line[i++] == '\n' || col == g_info.col - 1)
			col = 0;
		else
			col++;
	}
	return (col);
}

int		ft_getrow_fromstr(int cursor)
{
	int		i;
	int		row;
	int		col;

	i = g_info.strlen - g_info.cursor;
	row = g_info.crsr_row;
	col = g_info.crsr_col;
	while (i > cursor)
	{
		col = ft_line_len(i);
		if ((i = i - col - 1) > cursor)
			row -= 1;
		row = row - col / g_info.col;
	}
	while (i >= 0 && i < cursor)
	{
		if (g_info.line[i++] == '\n' || col >= g_info.col - 1)
		{
			col = 0;
			row++;
		}
		else
			col++;
	}
	return (row);
}
