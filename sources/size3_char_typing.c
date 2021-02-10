/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size3_char_typing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:55:41 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/05 13:15:00 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_size3_char(char *chr)
{
	if (chr[0] == ESC && chr[1] == '[')
	{
		if (chr[2] == 'D' && (g_info.strlen - g_info.cursor))
			ft_mv_left();
		else if (chr[2] == 'C' && g_info.cursor > 0)
			ft_mv_right();
		else if (chr[2] == 'A' && g_info.hist[g_info.hist_pos + 1])
			ft_history('+');
		else if (chr[2] == 'B' && g_info.hist_pos > -1)
			ft_history('-');
		else if (chr[2] == 'H' && g_info.strlen - g_info.cursor > 0)
			ft_ctrl_a();
		else if (chr[2] == 'F' && g_info.cursor > 0)
			ft_ctrl_e();
/*
		else
			ft_putchar_spe(chr);
		*/
	}
}

char	*ft_size4_char(char *line, char *chr)
{
	if (chr[0] == ESC && chr[1] == '[')
	{
		if (!ft_strcmp("3~", &chr[2]) && g_info.cursor > 0)
			line = ft_suppr_char(line);
	}
	return (line);
}

void	ft_size6_char(char *chr)
{
	ft_get_cursor_info();
	if (chr[0] == ESC && chr[1] == '[')
	{
		if (!ft_strcmp("1;5A", &chr[2]))
			ft_scroll(1, 'R');
		else if (!ft_strcmp("1;5B", &chr[2]))
			ft_scroll(1, 'F');
		else if (!ft_strcmp("1;2C", &chr[2]) && g_info.cursor)
			ft_reach_next_word();
		else if (!ft_strcmp("1;2D", &chr[2]) && g_info.cursor != g_info.strlen)
			ft_reach_previous_word();
		else
			ft_putchar_spe(chr);
	}
}
