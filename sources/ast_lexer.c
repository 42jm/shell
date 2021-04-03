/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

static int	lexer_opnew(t_astnode **at, char *input, size_t len)
{
	if (*at)
		return (token_delimit(*at, input, len));
	if (len != 0)
		return (put_error("non-existant token has len != 0", "lexer"));
	*at = token_new(input);
	if (!*at)
		return (1);
	return (token_delimit(*at, input, astlex_oplen(input)));
}

static int	lexer_ignore(t_astnode **at, char *input, size_t *alen)
{
	size_t	len;
	size_t	tmp;

	len = *alen;
	if (!*at)
	{
		*at = token_new(NULL);
		if (!*at)
			return (1);
	}
	if (ft_strchr("\\'\"", input[len]))
	{
		tmp = quotationlen(input + len, "\\'\"");
		if (tmp > 1)
			tmp--;
		len += tmp;
	}
	else if (ft_strchr("$`", input[len]))
		len += expansionlen(input + len);
	if (*alen != len)
		*alen = len;
	return (0);
}

static int	lex_default_case(size_t *alen, t_astnode **at)
{
	*alen = 1;
	*at = token_new(NULL);
	if (!*at)
		return (1);
	return (0);
}

int	ast_lexer(char *input, t_astnode **at)
{
	size_t		len;

	if (!input)
		return (1);
	*at = NULL;
	len = 0;
	while (len < ft_strlen(input) && input[len] != '\n')
	{
		if (ft_strchr("\\'\"$`", input[len]) && lexer_ignore(at, input, &len))
			return (1);
		else if (astlex_oplen(input + len) && (!*at || !ft_isdigit(input[len])))
			return (lexer_opnew(at, input, len));
		else if (ft_strchr(" \t", input[len]) && *at)
			return (token_delimit(*at, input, len));
		else if (ft_strchr(" \t", input[len]))
			input++;
		else if (*at && !(*at)->op)
			len++;
		else if (lex_default_case(&len, at))
			return (1);
	}
	if (*at)
		return (token_delimit(*at, input, len));
	return (0);
}
