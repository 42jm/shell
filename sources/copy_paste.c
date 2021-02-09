/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 20:57:00 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/09 21:02:08 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_ctrl_u(char *line)
{
	char	*res;
	int		i;
	int		len;

	len = g_info.strlen - g_info.cursor;
	i = 0;
	if (g_info.copy)
		free(g_info.copy);
	if (!(g_info.copy = ft_memalloc(len + 1)))
		return (NULL);
	ft_strncpy(g_info.copy, &line[i], len);
	if (!(res = ft_memalloc(g_info.strlen - len + 1)))
		return (NULL);
	ft_strncpy(res, &line[len], ft_strlen(&line[len]));
	ft_ctrl_a();
	ft_clean_after_cursor();
	g_info.strlen -= len;
	g_info.cursor -= len;
	ft_putstr(res);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	free(line);
	return (res);
}

char	*ft_ctrl_w(char *line)
{
	char	*res;
	int		i;
	int		len;

	len = g_info.strlen - g_info.cursor;
	i = ft_reach_previous_word();
	len -= i;
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
	ft_putstr(&res[i]);
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
	ft_clean_after_cursor();
	ft_putstr(g_info.copy);
	ft_get_cursor_pos();
	ft_putstr(&res[i + copylen]);
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
	free(line);
	return (res);
}
