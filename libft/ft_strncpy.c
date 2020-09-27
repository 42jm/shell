/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:27:28 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/13 15:16:57 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncpy(char *dst, const char *src, size_t dlen)
{
	size_t	i;

	i = 0;
	while (i < dlen && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i < dlen)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
