/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:52:36 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/30 20:08:34 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int 	wordcount(char const *s, char c)
{
	unsigned int	wc;
	unsigned int	i;

	wc = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			wc++;
		}
	}
	return (wc);
}

char	*writeword(char const *s, char c)
{
	unsigned int	i;
	char			*new;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	new = (char *)malloc(sizeof(char) * i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_free_fail(char **tab, int i)
{
	while (--i > -1)
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	**ft_strsplit(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	wc;
	char			**tab;

	if (!s)
		return (NULL);
	wc = wordcount(s, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = -1;
	while (++j < wc)
	{
		while (s[i] == c)
			i++;
		tab[j] = writeword(&s[i], c);
		if (!tab[j])
			return (ft_free_fail(tab, j));
		while (s[i] && s[i] != c)
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
