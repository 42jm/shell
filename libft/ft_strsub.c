/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:18:33 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 13:37:05 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!s)
		return (NULL);
	sub = (char *)malloc((len + 1) * sizeof(*s));
	i = -1;
	if (sub)
	{
		while (++i < len)
			sub[i] = s[i + (size_t)start];
		sub[len] = '\0';
	}
	return (sub);
}
