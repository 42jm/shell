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

#include "21sh.h"

t_astnode	*token_new(char *ptr)
{
	t_astnode	*token;

	/*
	ft_putstr("token_new(");
	ft_putstr(ptr);
	ft_putstr(")\n");
	*/

	token = (t_astnode *)malloc(sizeof(t_astnode));
	if (!token)
	{
		put_error("malloc failed to create struct", "token_new");
		return (NULL);
	}
	token->op = NULL;
	if (ptr)
	{
		token->op = ft_strndup(ptr, astlex_oplen(ptr));
		if (!token->op)
		{
			put_error("malloc failed to create op str", "token_new");
			return (NULL);
		}
	}
	token->content = NULL;
	token->next = NULL;
	return (token);
}

int			token_delimit(t_astnode *token, char *input, size_t len)
{
	/*
	ft_putstr("token_delimit(*, ");
	ft_putstr(input);
	ft_putstr(", ");
	ft_putnbr((int)len);
	ft_putstr(")\n");
	*/

	if (!token->op && !(token->content = (void *)ft_strndup(input, len)))
		return (put_error_ret("malloc failed", "token_delimit", 1));
	return (ast_lexer(input + len, &token->next));
}

size_t		quotationlen(char *s)
{
	size_t	len;
	char	quote;
	bool	backslashed;


	/*
	ft_putstr("quotationlen(");
	ft_putstr(s);
	*/

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
	//put_error("quote left unfinished", "quotationlen");
	return (0);
}

static size_t	expansionlen_param(char *s)
{
	size_t	len;
	bool	is_var;

	/*
	ft_putstr("expansionlen_param(");
	ft_putstr(s);
	*/

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

static size_t	expansionlen(char *s)
{
	size_t	len;
	size_t	tmp;
	char	*endseq;

	/*
	ft_putstr("expansionlen(");
	ft_putstr(s);
	*/

	endseq = NULL;
	len = 1;
	if (!ft_strncmp(s, "$((", 3) && (len = 3))		// arithmetic expansion
		endseq = "))";
	else if (!ft_strncmp(s, "$(", 2) && (len = 2))	
		endseq = ")";
	else if (!ft_strncmp(s, "${", 2) && (len = 2))	// parameter expansion
		endseq = "}";
	else if (*s == '`')								// command subsitution
		endseq = "`";
	else
		return (expansionlen_param(s));
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
	put_error("expansion not finished", "expansionlen");
	return (0);
}

int			ast_lexer(char *input, t_astnode **at)
{
	size_t		len;

	/*
	ft_putstr("lexer(");
	ft_putstr(input);
	*/

	if (!input)
		return (1);
	*at = NULL;
	len = 0;
	while (input[len] && input[len] != '\n')
	{
		if (ft_strchr("\\'\"", input[len]))
		{
			//ft_putendl("4: quotation");
			if (!*at && !(*at = token_new(NULL)))
				return (1);
			len += quotationlen(input + len);
		}
		else if (ft_strchr("$`", input[len]))
		{
			//ft_putendl("5: expand/substitute");
			if (!*at && !(*at = token_new(NULL)))
				return (1);
			len += expansionlen(input + len);
		}
		else if (astlex_oplen(input + len) && (!*at || !ft_isdigit(input[len])))
		{
			//ft_putendl("6+2+3: operator recognition, aggregation, delimitation");
			if (*at)
				return (token_delimit(*at, input, len));
			if (len != 0)
				return (put_error("non-existant token has len != 0", "lexer"));
			if (!(*at = token_new(input)))
				return (1);
			return (token_delimit(*at, input, astlex_oplen(input)));
		}
		else if (ft_strchr(" \t", input[len]))
		{
			//ft_putendl("8: blank delimitation");
			if (*at)
				return (token_delimit(*at, input, len));
			input++;
		}
		else if (*at && !(*at)->op)
		{ 
			//ft_putendl("9: word aggregation");
			len++;
		}
		else if (*input == '#')
		{
			//ft_putendl("10: comments handling");
			while (*input && *input != '\n')
				input++;
		}
		else
		{
			//ft_putendl("11: word recognition");
			if (!(*at = token_new(NULL)))
				return (1);
			len = 1;
		}
	}
	//ft_putendl("1+7: end of input + end of line");
	if (*at)
		return (token_delimit(*at, input, len));
	return (0);
}
