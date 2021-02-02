/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:17:36 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 15:42:03 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsz)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(dst);
	i = 0;
	while (len + i + 1 < dstsz && src[i])
	{
		dst[len + i] = src[i];
		i++;
	}
	if (dstsz && len < dstsz)
	{
		dst[len + i] = '\0';
		len += ft_strlen(src);
	}
	else
		len = dstsz + ft_strlen(src);
	return (len);
}
