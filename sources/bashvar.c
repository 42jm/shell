/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bashvar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

size_t	bashvar_len(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	if (ft_strchr("#?", *str))
		return (1);
	if (*str == '{')
		return (ft_strclen(str, '}'));
	len = 0;
	while (ft_isdigit(str[len]))
		len++;
	while (!ft_isdigit(*str) && (str[len] == '_' || ft_isalnum(str[len])))
		len++;
	return (len);
}

size_t	bashvar_len_until_next_var(char *s)
{
	size_t	len;
	size_t	i;
	size_t	quote_len;
	int		inside_doubles;

	len = ft_strlen(s);
	i = 0;
	inside_doubles = 0;
	while (i < len)
	{
		if (s[i] == '"')
			inside_doubles = 1 - inside_doubles;
		if (s[i] == '$')
			return (i + 1);
		if (inside_doubles)
			quote_len = quotationlen(s + i, "\\");
		else
			quote_len = quotationlen(s + i, "\\'");
		if (quote_len)
			i += quote_len;
		else
			i++;
	}
	return (0);
}
