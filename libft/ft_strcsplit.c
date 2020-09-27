/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:49:44 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 18:07:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_splitcount(char *s, char c)
{
	char	count;

	count = 0;
	while (*s)
	{
		if (*s != c && *s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
		while (*s == c && *s)
			s++;
	}
	return (count);
}

static size_t	ft_nextlen(char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s == c && *s)
		s++;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strcsplit(char const *s, char c)
{
	char	*str;
	size_t	str_count;
	char	**split;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	str_count = ft_splitcount(str, c);
	split = (char **)(malloc((str_count + 1) * sizeof(char *)));
	if (!split)
		return (NULL);
	i = 0;
	while (i < str_count && *str)
	{
		while (*str == c && *str)
			str++;
		split[i] = ft_strndup(str, ft_nextlen(str, c));
		while (*str != c && *str)
			str++;
		i++;
	}
	split[str_count] = NULL;
	return (split);
}
