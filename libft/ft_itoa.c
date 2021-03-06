/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:10:57 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 13:05:48 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_chrcount(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		n /= 10;
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		chr_count;
	char	*str;
	int		sign;

	chr_count = ft_chrcount(n);
	if (n < 0)
		chr_count++;
	str = (char *)malloc((chr_count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[chr_count] = '\0';
	sign = 0;
	if (n < 0)
	{
		str[0] = '-';
		sign = 1;
	}
	while (--chr_count >= sign)
	{
		str[chr_count] = '0' + (1 + -2 * sign) * (n % 10);
		n /= 10;
	}
	return (str);
}
