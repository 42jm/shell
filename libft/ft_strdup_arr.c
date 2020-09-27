/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:27:59 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/15 16:42:52 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_arr(char **src)
{
	size_t	sz;
	char	**dup;
	size_t	i;

	sz = ft_strlen_arr((const char **)src);
	dup = (char **)malloc(sizeof(*dup) * (sz + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < sz)
	{
		dup[i] = ft_strdup(src[i]);
		i++;
	}
	dup[sz] = NULL;
	return (dup);
}
