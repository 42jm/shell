/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/13 18:05:56 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrchr(const char *s, int c)
{
	char	chr;
	int		len;

	chr = (char)c;
	len = (int)ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == chr)
			return ((char *)&s[len]);
		len--;
	}
	return (NULL);
}
