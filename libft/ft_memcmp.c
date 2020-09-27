/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:14:20 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 09:40:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_memcmp(const void *m1, const void *m2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	int				diff;
	size_t			i;

	if (!n)
		return (0);
	s1 = (unsigned char *)m1;
	s2 = (unsigned char *)m2;
	diff = (int)(*s1 - *s2);
	i = 1;
	while (!diff && i < n)
	{
		s1++;
		s2++;
		diff = (int)(*s1 - *s2);
		i++;
	}
	return (diff);
}
