/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull_scratch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:40:03 by quegonza          #+#    #+#             */
/*   Updated: 2020/12/10 22:38:35 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

void	ft_putchar_spe(char *c)
{
	int		i;

	i = -1;
	ft_putstr("  [");
	while (c[++i])
	{
		ft_putnbr(c[i]);
		ft_putstr("][");
	}
	i = -1;
	while (c[++i])
	{
		if (c[i] > 32 && c[i] < DEL)
			ft_putchar(c[i]);
		else
			ft_putchar('^');
	}
	ft_putstr("  ");
	tputs(tgoto(g_info.cap.cm, g_info.crsr_col, g_info.crsr_row), 1, ft_putc);
}

char	*ft_addchar(char *line, char *chr)
{
	char	*res;

	res = ft_strjoin(line, chr);
	free(line);
	return (res);
}

