/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:03:52 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/11 11:57:18 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int value, int base)
{
	int		i;
	char	*nbr;
	int		neg;

	i = 1;
	neg = 0;
	if (value < 0 && base == 10)
		neg = 1;
	if (value < 0)
		value *= -1;
	while (ft_pow(base, i) - 1 < value)
		i++;
	nbr = (char *)malloc(sizeof(nbr) * i);
	nbr[i + neg] = '\0';
	while (i-- > 0)
	{
		if (value % base > 9)
			nbr[i + neg] = (value % base) + 'a' - 10;
		else
			nbr[i + neg] = (value % base) + '0';
		value = value / base;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}
