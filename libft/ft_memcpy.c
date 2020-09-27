/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:54:26 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 16:21:15 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (dest);
}
