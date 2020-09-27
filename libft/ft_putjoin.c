/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:25:20 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/11 16:43:41 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putjoin(size_t len, ...)
{
	va_list	ap;
	size_t	i;

	va_start(ap, len);
	i = 0;
	while (i < len)
	{
		ft_putstr(va_arg(ap, char *));
		i++;
	}
}
