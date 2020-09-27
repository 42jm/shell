/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:25:15 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 13:33:15 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*join;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)malloc((len1 + len2 + 1) * sizeof(*s1));
	i = -1;
	if (join)
	{
		while (++i < len1)
			join[i] = s1[i];
		i--;
		while (++i < len1 + len2)
			join[i] = s2[i - len1];
		join[len1 + len2] = '\0';
	}
	return (join);
}
