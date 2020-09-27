/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 12:52:59 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/25 12:53:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(void *adr, size_t len, int fd, char pad)
{
	size_t		i;
	char		*ptr;
	static char	digit[16] = "0123456789abcdef";
	char		first;

	i = 0;
	ptr = (char *)adr;
	first = 1;
	while (i < len)
	{
		if (!first || pad || ((ptr[i] & 0xf0) >> 4))
			ft_putchar_fd(digit[(ptr[i] & 0xf0) >> 4], fd);
		ft_putchar_fd(digit[ptr[i] & 0x0f], fd);
		first = 0;
		i++;
	}
}
