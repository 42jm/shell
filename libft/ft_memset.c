/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:47:21 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 16:21:47 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char	*sbyte;
	size_t	i;

	sbyte = (char *)s;
	i = 0;
	while (i < n)
	{
		sbyte[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
