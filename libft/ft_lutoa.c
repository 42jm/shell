/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:10:57 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 13:05:48 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_chrcount(uint64_t n)
{
	size_t	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_lutoa(uint64_t n)
{
	size_t	chr_count;
	char	*str;

	chr_count = ft_chrcount(n);
	str = (char *)malloc((chr_count + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[chr_count] = '\0';
	while (chr_count-- > 0)
	{
		str[chr_count] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
