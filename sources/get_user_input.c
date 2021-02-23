/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 02:00:55 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/23 17:21:29 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

char	*ft_current_char(char *buf, int *len)
{
	*len = 0;
	ft_bzero(buf, 16);
	*len = read(g_info.fdr, buf, 16);
	return (buf);
}

int 	ft_key_interaction(void)
{
	char	chr[16];
	int		len;

	if (!ft_current_char(chr, &len))
		return (0);
	else if (len == 1)
		g_info.line = ft_size1_char(g_info.line, chr);
	else if (len == 2)
		g_info.line = ft_size2_char(g_info.line, chr);
	else if (len == 3)
		ft_size3_char(chr);
	else if (len == 4)
		g_info.line = ft_size4_char(g_info.line, chr);
	else if (len == 6)
		ft_size6_char(chr);
	return (1);
}

int 	ft_new_input(void)
{
	if (tcsetattr(0, 0, &(g_info.s_termios)) == -1)
		return (0);
	ft_get_cursor_info();
	g_info.cursor = 0;
	g_info.hist_pos = -1;
	g_info.strlen = 0;
	g_info.prompt = g_info.crsr_col;
	g_info.line = ft_memalloc(1);
	if (!(g_info.line))
		return (0);
	signal(SIGWINCH, ft_sighandler_winsize_change);
	signal(SIGINT, ft_sighandler_ctrl_c);
	signal(SIGCONT, ft_sighandler_ctrl_z_return);
	g_info.exit = 0;
	return (1);
}

char	*ft_get_user_input(void)
{
	if (!ft_new_input())
		return (NULL);
	while (!ft_line_validation())
	{
		if (!ft_key_interaction())
		{
			free(g_info.line);
			return (NULL);
		}
	}
	g_info.hist = ft_history_new();
	if (!(g_info.hist))
	{
		free(g_info.line);
		return (NULL);
	}
	if (tcsetattr(0, 0, &(g_info.s_termios_backup)) == -1)
		ft_putstr("error: Can't recover terminal configuration\n");
	return (g_info.line);
}

void	ft_end_clean(char *end_message)
{
	if (tcsetattr(0, 0, &(g_info.s_termios_backup)) == -1)
		ft_putstr("error: Can't recover terminal configuration\n");
	ft_free_tabzero(g_info.hist);
	if (g_info.copy)
		free(g_info.copy);
	if (g_info.temp)
		free(g_info.temp);
	close(g_info.fdr);
	close(g_info.fdw);
	if (end_message)
		ft_putstr(end_message);
}
