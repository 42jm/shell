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

#include "header_42sh.h"

size_t	parenlen(char *str)
{
	size_t	len;
	size_t	str_len;
	size_t	count;
	char	parenchr[2];

	parenchr[0] = *str;
	parenchr[1] = '}';
	if (parenchr[0] == '(')
		parenchr[1] = ')';
	else if (parenchr[0] != '{')
		return (0);
	len = 1;
	count = 1;
	str_len = ft_strlen(str);
	while (len < str_len && count)
	{
		if (str[len] == parenchr[1])
			count--;
		else if (str[len] == parenchr[0])
			count++;
		len++;
	}
	if (count)
		return (0);
	return (len);
}

size_t	quotationlen(char *s, char *quotes)
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
		backslashed = false;
		if (s[len] == '\\' && quote == '"' && !backslashed)
			backslashed = true;
		len++;
	}
	return (0);
}

static size_t	expansionlen_until(char *s, char *endseq)
{
	size_t	len;
	int		tmp;

	len = 0;
	while (s[len])
	{
		tmp = -1;
		if (ft_strchr("$`", s[len]))
			tmp = expansionlen(s + len);
		else if (ft_strchr("\\'\"", s[len]))
			tmp = quotationlen(s + len, "\\'\"");
		else if (!ft_strncmp(s + len, endseq, ft_strlen(endseq)))
			return (len + ft_strlen(endseq));
		if (!tmp)
			return (0);
		if (tmp > 0)
			len += tmp;
		else
			len++;
	}
	put_error("warning: missing end sequence", endseq);
	return (0);
}

size_t	expansionlen(char *s)
{
	size_t	len;
	size_t	tmp;
	char	*endseq;

	endseq = NULL;
	if (!ft_strncmp(s, "$((", 3))
		endseq = "))";
	else if (!ft_strncmp(s, "$(", 2))
		endseq = ")";
	else if (!ft_strncmp(s, "${", 2))
		endseq = "}";
	else if (*s == '`')
		endseq = "`";
	else
		return (bashvar_len(s + 1));
	len = 1;
	if (*s == '$')
		len += ft_strlen(endseq);
	tmp = expansionlen_until(s + len, endseq);
	if (!tmp)
		return (0);
	return (len + tmp);
}
