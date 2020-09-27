/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:49:44 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 12:56:50 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_splitcount(size_t len, size_t n)
{
	return (len / n + (len % n ? 1 : 0));
}

char			**ft_strnsplit(char const *s, size_t n)
{
	char	*str;
	size_t	str_count;
	char	**split;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	str_count = ft_splitcount(ft_strlen(s), n);
	split = (char **)(malloc((str_count + 1) * sizeof(char *)));
	if (!split)
		return (NULL);
	i = 0;
	while (i < str_count && *str)
	{
		split[i] = ft_strndup(str + i * n, n);
		i++;
	}
	split[str_count] = NULL;
	return (split);
}
