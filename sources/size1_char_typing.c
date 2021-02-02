/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size1_char_typing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:50:07 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/02 01:19:09 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_size1_char(char *line, char *chr)
{
	char c;

	c = chr[0];
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
	else if (c == CTRL_Y)
		line = ft_ctrl_y(line);
	return (line);
}

char	*ft_ctrl_u(char *line)
{
	if (line)
		ft_putstr("^U");
	return (line);
}

char	*ft_ctrl_w(char *line)
{
	char	*res;
	int		i;
	int		len;


	i = ft_reach_previous_word();
	len = g_info.strlen - g_info.cursor - i;
	if (g_info.copy)
		free(g_info.copy);
	if (!(g_info.copy = ft_memalloc(len + 1)))
		return (NULL);
	ft_strncpy(g_info.copy, &line[i], len);
	if (!(res = ft_memalloc(g_info.strlen - len + 1)))
		return (NULL);
	ft_strncpy(res, line, i);
	ft_strncpy(&res[i], &line[i + len], ft_strlen(&line[i + len]));
	ft_clean_after_cursor();
	g_info.strlen -= len;
	g_info.cursor -= len;
	ft_putstr(&line[i + len]);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	free(line);
	return (res);
}

char	*ft_ctrl_y(char *line)
{
	char	*res;
	int		copylen;
	int		i;

	copylen = ft_strlen(g_info.copy);
	if (!(res = ft_memalloc(g_info.strlen + copylen + 1)))
		return (NULL);
	i = g_info.strlen - g_info.cursor;
	ft_strncpy(res, line, i);
	ft_strcpy(&res[i], g_info.copy);
	ft_strcpy(&res[i + copylen], &line[i]);
	g_info.strlen += copylen;
	ft_putstr(&res[i]);
	free(line);
	return (res);
}

void	ft_ctrl_e()
{
	ft_get_cursor_info();
	g_info.crsr_col = ft_getcol_fromstr(g_info.strlen);
	g_info.crsr_row = ft_getrow_fromstr(g_info.strlen);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	g_info.cursor = 0;
}

void	ft_ctrl_a()
{
	ft_get_cursor_info();
	g_info.crsr_col = ft_getcol_fromstr(0);
	g_info.crsr_row = ft_getrow_fromstr(0);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	g_info.cursor = g_info.strlen;
}

char	*ft_ctrl_d(char *line)
{
	if (!(g_info.strlen))
	{
		g_info.exit = 1;
		free(g_info.line);
		g_info.line = ft_strdup("exit");
	}
	else if (g_info.cursor)
		line = ft_suppr_char(line);
	return (line);
}

void	ft_scroll(int nb, char opt)
{
	if (opt == 'R')
	{
		while (--nb >= 0)
		{
			tputs(tgetstr("sr", NULL), g_info.row, ft_putc);
		}
	}
	if (opt == 'F')
	{
		while (--nb >= 0)
		{
			tputs(tgetstr("sf", NULL), g_info.row, ft_putc);
		}
	}
}
