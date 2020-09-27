/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:27:59 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/15 16:42:52 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	sz;
	size_t	i;

	sz = ft_strlen(src);
	i = -1;
	while (++i < sz)
		dst[i] = src[i];
	dst[sz] = '\0';
	return (dst);
}
