/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 12:34:14 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:59:58 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_iter(int n, int fd, int sign)
{
	if (n < -9 || 9 < n)
		ft_iter(n / 10, fd, sign);
	ft_putchar_fd((char)('0' + sign * (n % 10)), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_iter(n, fd, -1);
	}
	else
		ft_iter(n, fd, 1);
}
