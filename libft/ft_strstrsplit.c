/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:49:44 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 18:07:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_splitcount(char *s, char *delim)
{
	char	count;

	count = 0;
	while (*s)
	{
		if (!ft_strchr(delim, *s) && *s)
		{
			count++;
			while (!ft_strchr(delim, *s) && *s)
				s++;
		}
		while (ft_strchr(delim, *s) && *s)
			s++;
	}
	return (count);
}

static size_t	ft_nextlen(char *s, char *delim)
{
	size_t	len;

	len = 0;
	while (ft_strchr(delim, *s) && *s)
		s++;
	while (!ft_strchr(delim, *s) && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_strstrsplit(char *s, char *delim)
{
	char	*str;
	size_t	str_count;
	char	**split;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	str_count = ft_splitcount(str, delim);
	split = (char **)(malloc((str_count + 1) * sizeof(char *)));
	if (!split)
		return (NULL);
	i = 0;
	while (i < str_count && *str)
	{
		while (ft_strchr(delim, *str) && *str)
			str++;
		split[i] = ft_strndup(str, ft_nextlen(str, delim));
		while (!ft_strchr(delim, *str) && *str)
			str++;
		i++;
	}
	split[str_count] = NULL;
	return (split);
}
