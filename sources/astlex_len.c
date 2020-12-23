/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astlex_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

size_t			parenlen(char *str)
{
	size_t	len;
	size_t	str_len;
	size_t	count;
	char	openchr;
	char	closechr;

	openchr = *str;
	if (openchr == '(')
		closechr = ')';
	else if (openchr == '{')
		closechr = '}';
	else
		return (0);
	len = 1;
	count = 1;
	str_len = ft_strlen(str);
	while (len < str_len && count)
	{
		if (str[len] == closechr)
			count--;
		else if (str[len] == openchr)
			count++;
		len++;
	}
	return (count ? 0 : len);
}

size_t			quotationlen(char *s, char *quotes)
{
	size_t	len;
	char	quote;
	bool	backslashed;

	if (!s)
		return (0);
	quote = *s;
	if (!ft_strchr(quotes, quote))
		return (0);
	if (quote == '\\')
		return (2);
	len = 1;
	backslashed = false;
	while (s[len])
	{
		if (s[len] == quote && !backslashed)
			return (len + 1);
		if (s[len] == '\\' && quote == '"' && !backslashed)
			backslashed = true;
		else if (backslashed)
			backslashed = false;
		len++;
	}
	return (0);
}

static size_t	expansionlen_until(char *s, char *endseq)
{
	size_t	len;
	size_t	tmp;

	len = 0;
	while (s[len])
	{
		if (ft_strchr("$`", s[len]))
		{
			if (!(tmp = expansionlen(s + len)))
				return (0);
			len += tmp;
		}
		else if (ft_strchr("\\'\"", s[len]))
		{
			if (!(tmp = quotationlen(s + len, "\\'\"")))
				return (0);
			len += tmp;
		}
		else if (!ft_strncmp(s + len, endseq, ft_strlen(endseq)))
			return (len + ft_strlen(endseq));
		else
			len++;
	}
	put_error("warning: missing end sequence", endseq);
	return (0);
}

size_t			expansionlen(char *s)
{
	size_t	len;
	size_t	tmp;
	char	*endseq;

	endseq = NULL;
	len = 1;
	if (!ft_strncmp(s, "$((", 3) && (len = 3))
		endseq = "))";
	else if (!ft_strncmp(s, "$(", 2) && (len = 2))
		endseq = ")";
	else if (!ft_strncmp(s, "${", 2) && (len = 2))
		endseq = "}";
	else if (*s == '`')
		endseq = "`";
	else
		return (bashvar_len(s + 1));
	tmp = expansionlen_until(s + len, endseq);
	if (!tmp)
		return (0);
	return (len + tmp);
}
