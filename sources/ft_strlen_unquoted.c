/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_unquoted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:34:08 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

size_t	ft_strclen_unquoted(char *s, char chr)
{
	size_t	len;
	size_t	i;
	size_t	quote_len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (s[i] == chr)
			return (i + 1);
		quote_len = quotationlen(s + i);
		if (quote_len)
			i += quote_len;
		else
			i++;
	}
	return (0);
}

size_t	ft_stralen_unquoted(char *s, char *chars)
{
	size_t	len;
	size_t	tmp;

	if (!chars)
		return (0);
	len = 0;
	while (*chars)
	{
		tmp = ft_strclen_unquoted(s, *chars);
		if (tmp && (tmp < len || !len))
			len = tmp;
		chars++;
	}
	return (len);
}
