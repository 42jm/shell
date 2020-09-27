/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:34:08 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchr(const char *s, int c)
{
	unsigned char	chr;
	size_t			len;
	size_t			i;

	chr = (unsigned char)c;
	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (*s == chr)
			return ((char *)s);
		i++;
		s++;
	}
	return (NULL);
}
