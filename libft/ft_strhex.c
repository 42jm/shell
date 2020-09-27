/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:40:28 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/08 14:14:17 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strhex(unsigned char *ptr, size_t n)
{
	char		*hex;
	size_t		i;
	static char	digits[16] = "0123456789abcdef";

	hex = (char *)malloc(sizeof(char) * (n * 2 + 1));
	hex[n * 2] = '\0';
	i = 0;
	while (i < n)
	{
		hex[i * 2] = digits[ptr[i] >> 4];
		hex[i * 2 + 1] = digits[ptr[i] & 0x0f];
		i++;
	}
	return (hex);
}
