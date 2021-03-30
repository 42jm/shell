/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull_scratch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:40:03 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/28 18:46:44 by quegonza         ###   ########.fr       */
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

void	ft_display_history(void)
{
	int	i;

	i = 0;
	while (g_info.hist[i])
	{
		ft_putstr("---> ");
		ft_putstr(g_info.hist[i]);
		ft_putchar('\n');
		i++;
	}
}
