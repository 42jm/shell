/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:30:11 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 16:37:53 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*sbyte;
	size_t			i;

	sbyte = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*sbyte == (unsigned char)c)
			return ((void *)sbyte);
		sbyte++;
		i++;
	}
	return (NULL);
}
