/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stralen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:34:08 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_stralen(char *s, char *delims)
{
	size_t	len;
	size_t	tmp;

	if (!s || !delims)
		return (0);
	len = 0;
	while (*delims)
	{
		tmp = ft_strclen(s, *delims);
		if (tmp < len)
			len = tmp;
		delims++;
	}
	return (len);
}
