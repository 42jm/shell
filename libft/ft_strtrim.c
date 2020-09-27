/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:37:32 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 14:41:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	size_t	len;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	start = 0;
	while (s[start] && ft_strchr(" \t\n", (int)s[start]))
		start++;
	if (start == len)
		return (ft_strnew(0));
	end = 0;
	while (s[len - end - 1] && ft_strchr(" \t\n", (int)s[len - end - 1]))
		end++;
	return (ft_strsub(s, start, (unsigned int)(len - start - end)));
}
