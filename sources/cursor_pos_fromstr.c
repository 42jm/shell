/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_pos_fromstr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 20:19:20 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/13 20:42:56 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_getcol_fromstr(int cursor)
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

int 	ft_getrow_fromstr_end(int *i, int *row, int *col, int cursor)
{
	if (*i >= 0)
	{
		while (*i < cursor)
		{
			if (g_info.line[*i] == '\n' || *col >= g_info.col - 1)
			{
				*col = 0;
				(*row)++;
			}
			else
				(*col)++;
			(*i)++;
		}
	}
	return (*row);
}

int 	ft_getrow_fromstr(int cursor)
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
		i = i - col - 1;
		if (i > cursor)
			row -= 1;
		row = row - col / g_info.col;
	}
	return (ft_getrow_fromstr_end(&i, &row, &col, cursor));
}
