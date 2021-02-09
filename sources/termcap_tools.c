/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:44:05 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/09 21:08:10 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

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
	write(1, &c, 1);
	return (c);
}

void	ft_usecap(char *cap)
{
	cap = tgetstr(cap, NULL);
	tputs(cap, 1, ft_putc);
}

int		ft_line_len(int i)
{
	int		j;

	if (!i)
		j = 0;
	else
		j = i - 1;
	while (j > 0 && g_info.line[j] != '\n')
		j--;
	if (!j)
		return (i + g_info.prompt);
	return (i - j - 1);
}
