/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:10:57 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 13:05:48 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static long long int	ft_chrcount(long long int n)
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

char					*ft_ltoa(long long int n)
{
	long long int		chr_count;
	char				*str;
	long long int		sign;

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
		str[chr_count] = '0' + (1 + sign * -2) * (n % 10);
		n /= 10;
	}
	return (str);
}
