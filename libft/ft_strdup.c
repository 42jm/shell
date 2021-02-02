/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:40:59 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/24 16:04:22 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	size_t	sz;
	char	*dup;
	size_t	i;

	if (!str)
		return (NULL);
	sz = ft_strlen(str);
	dup = (char *)malloc((sz + 1) * sizeof(char));
	ft_bzero(dup, sz + 1);
	i = 0;
	if (!dup)
		return (NULL);
	while (i < sz)
	{
		dup[i] = str[i];
		i++;
	}
	return (dup);
}
