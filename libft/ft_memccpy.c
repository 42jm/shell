/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:05:13 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 16:18:47 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char	*dbyte;
	char	*sbyte;
	size_t	i;

	dbyte = (char *)dest;
	sbyte = (char *)src;
	i = 0;
	while (i < n)
	{
		dbyte[i] = sbyte[i];
		if (dbyte[i] == (char)c)
			return ((void *)&dbyte[i + 1]);
		i++;
	}
	return (NULL);
}
