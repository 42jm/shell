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

size_t			quotationlen(char *s)
{
	size_t	len;
	char	quote;
	bool	backslashed;

	if (!s)
		return (0);
	quote = *s;
	if (!ft_strchr("\\'\"", quote))
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

static size_t	expansionlen_param(char *s)
{
	size_t	len;
	bool	is_var;

	if (!s || *s != '$')
		return (0);
	len = 1;
	is_var = false;
	if (s[1] == '_' || ft_isalpha(s[1]))
		is_var = true;
	while (s[len])
	{
		if (is_var && s[len] != '_' && !ft_isalnum(s[len]))
			return (len);
		if (!is_var && !ft_isdigit(s[len]))
			return (len);
		len++;
	}
	return (len);
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
			if (!(tmp = quotationlen(s + len)))
				return (0);
			len += tmp;
		}
		else if (!ft_strncmp(s + len, endseq, ft_strlen(endseq)))
			return (len + ft_strlen(endseq));
		else
			len++;
	}
	put_error("missing end sequence", endseq);
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
		return (expansionlen_param(s));
	tmp = expansionlen_until(s + len, endseq);
	if (!tmp)
		return (0);
	return (len + tmp);
}
