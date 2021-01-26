/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:44:05 by quegonza          #+#    #+#             */
/*   Updated: 2021/01/26 07:14:07 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_clean_after_cursor(void)
{
	int		i;
	int		maxcol;

	ft_get_cursor_info();
	i = g_info.crsr_col;
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

void	ft_erase_crsrline(void)
{
	int		i;
	int		maxcol;

	ft_get_cursor_info();
	i = g_info.crsr_col;
	maxcol = g_info.col;
	while (++i < maxcol)
		ft_putchar(' ');
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
}

int		ft_error(char *cause, int code)
{
	if (cause)
		ft_putstr(cause);
	else
		ft_putstr("\nerror\n");
	return (code);
}

int		ft_putc(int c)
{
	write (1, &c, 1);
	return (c);
}

void	ft_usecap(char *cap)
{
	cap = tgetstr(cap, NULL);
	tputs (cap, 1, ft_putc);
}

