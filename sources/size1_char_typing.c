/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size1_char_typing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgaveria <lgaveria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:50:07 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/05 22:51:09 by lgaveria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_size1_char(char *line, char *chr)
{
	char	c;

	c = chr[0];
	if (g_info.sigcont)
		return (line);
	if (c == '\n')
		ft_ctrl_e();
	if ((32 <= c && c < DEL) || c == '\n')
		line = ft_insert_char(line, c);
	else if (c == DEL && g_info.strlen != g_info.cursor)
		line = ft_del_char(line);
	else if (c == CTRL_A && g_info.strlen != g_info.cursor)
		ft_ctrl_a();
	else if (c == CTRL_D)
		line = ft_ctrl_d(line);
	else if (c == CTRL_E && g_info.cursor)
		ft_ctrl_e();
	else if (c == CTRL_U && g_info.strlen != g_info.cursor)
		line = ft_ctrl_u(line);
	else if (c == CTRL_W && g_info.strlen != g_info.cursor)
		line = ft_ctrl_w(line);
	else if (c == CTRL_Y && g_info.copy[0])
		line = ft_ctrl_y(line);
	return (line);
}

void	ft_ctrl_a(void)
{
	ft_get_cursor_info();
	g_info.crsr_row = ft_getrow_fromstr(0);
	g_info.crsr_col = ft_getcol_fromstr(0);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	g_info.cursor = g_info.strlen;
}

void	ft_ctrl_e(void)
{
	ft_get_cursor_info();
	g_info.crsr_row = ft_getrow_fromstr(g_info.strlen);
	g_info.crsr_col = ft_getcol_fromstr(g_info.strlen);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	g_info.cursor = 0;
}

char	*ft_ctrl_d(char *line)
{
	if (!(g_info.strlen))
	{
		g_info.exit = 1;
		ft_strdel(&line);
		line = ft_strdup("exit");
	}
	else if (!(g_info.cursor) && g_info.line[g_info.strlen - 1] == '\n')
	{
		g_info.line[g_info.strlen - 1] = '\0';
		g_info.exit = 1;
	}
	else if (g_info.cursor)
		line = ft_suppr_char(line);
	return (line);
}
