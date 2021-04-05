/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_dots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:42:55 by quegonza          #+#    #+#             */
/*   Updated: 2021/03/30 19:47:34 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"
#include "quegonza.h"

int 	ft_chk_dot(char *str, char *dots)
{
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(dots);
	if (!ft_strncmp(str, dots, len))
		if (!str[len] || str[len] == '/')
			return (0);
	return (1);
}

char	*ft_ddots(char *str, int i, int todl)
{
	int		j;
	char	*res;

	j = 0;
	res = (char *)ft_memalloc(ft_strlen(str) - todl + 1);
	if (!res)
		return (NULL);
	while (j <= i)
	{
		res[j] = str[j];
		j++;
	}
	while (str[j + todl])
	{
		res[j] = str[j + todl];
		j++;
	}
	return (res);
}

char	*ft_replace_ddots_rest(char *str, int i)
{
	char	*tmp;
	int		slh;
	int		todl;

	slh = 0;
	todl = 1;
	if (str[i + 2] == '/')
		todl++;
	while (i && slh != 2)
	{
		i--;
		todl++;
		if (str[i] == '/')
			slh++;
	}
	tmp = str;
	str = ft_ddots(str, i, todl);
	if (!str)
		return (NULL);
	free(tmp);
	return (str);
}

char	*ft_replace_ddots(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if ((!i || str[i - 1] == '/') && !ft_chk_dot(&str[i], ".."))
		{
			str = ft_replace_ddots_rest(str, i);
			if (!str)
				return (NULL);
			i = -1;
		}
		i++;
	}
	return (str);
}
