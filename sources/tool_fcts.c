/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:44:05 by quegonza          #+#    #+#             */
/*   Updated: 2021/02/22 19:16:32 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_error(char *cause, int code)
{
	if (cause)
		ft_putstr(cause);
	else
		ft_putstr("\nerror\n");
	return (code);
}

int 	ft_putc(int c)
{
	write(1, &c, 1);
	return (c);
}

int 	ft_isoneof_chr(char chr, char *chrs)
{
	while (*chrs)
	{
		if (chr == *chrs)
			return (1);
		chrs++;
	}
	return (0);
}
