/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:34:08 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strclen(char *s, char chr)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s) + 1;
	i = 0;
	while (i < len)
	{
		if (*s == chr)
			return (i + 1);
		i++;
		s++;
	}
	return (0);
}
