/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quegonza <quegonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:44:05 by quegonza          #+#    #+#             */
/*   Updated: 2021/04/03 19:25:36 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"

int 	ft_error(char *cause, int code)
{
	if (cause)
		ft_putstr(cause);
	else
		ft_putstr("\nerror\n");
	return (code);
}

int 	ft_putc(int c)
{
	write(1, &c, 1);
	return (c);
}

int 	ft_isoneof_chr(char chr, char *chrs)
{
	while (*chrs)
	{
		if (chr == *chrs)
			return (1);
		chrs++;
	}
	return (0);
}

char	*ft_first_word(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	j = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
	{
		i++;
		j++;
	}
	if (j)
	{
		res = ft_memalloc(j + 1);
		if (!res)
			return (NULL);
		ft_strncpy(res, &str[i - j], j);
	}
	else
		return (NULL);
	return (res);
}

char	*ft_replace_first_word(char *res, char *str)
{
	int		i;
	int		reslen;
	char	*new;

	i = 0;
	reslen = ft_strlen(res);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\n')
		i++;
	new = ft_memalloc(ft_strlen(&str[i]) + reslen + 1);
	ft_strcpy(new, res);
	if (reslen)
		ft_strcpy(&new[reslen], &str[i]);
	g_info.strlen = g_info.strlen - i + reslen;
	free(res);
	free(str);
	return (new);
}
