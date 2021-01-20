/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 06:16:23 by quegonza          #+#    #+#             */
/*   Updated: 2020/12/10 22:37:55 by quegonza         ###   ########.fr       */
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

void	ft_get_cursor_pos()
{
	int		i;
	char	buf[15];

	write(1, "\033[6n", 4);
	ft_bzero(buf, 15);
	if(read(1, buf, 14) == -1)
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

void	ft_get_term_size()
{
	struct winsize ws;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	g_info.col = ws.ws_col;
	g_info.row = ws.ws_row;
}

void	ft_get_cursor_info()
{
	ft_get_term_size();
	ft_get_cursor_pos();
}
