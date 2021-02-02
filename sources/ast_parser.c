/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int	handle_separ(t_astnode *token, t_astnode *prev, t_astnode *head)
{
	int	ret;

	if (!prev)
		return (put_error("nothing before token", token->op));
	prev->next = NULL;
	ret = ast_parser(&head);
	if (ret)
		return (ret);
	token->content = head;
	return (ast_parser(&token->next));
}

static int	token_handler(t_astnode **at, t_astnode *prev, t_astnode *head)
{
	t_astnode	*token;

	token = *at;
	if (!token || !token->op)
		return (put_error("no token or no token->op", "token_handler"));
	if (!ft_strcmp(token->op, "&&") || !ft_strcmp(token->op, "||"))
		return (handle_andor(at, prev, head));
	if (ft_strlen(token->op) == 1 && ft_strchr(";&|", *token->op))
		return (handle_separ(token, prev, head));
	return (put_error(token->op, "token not handled"));
}

static int	curly_update(t_astnode *token, int curly)
{
	int	closing_curly;

	if (curly && !token->op && !ft_strcmp(token->content, "}"))
		return (curly - 1);
	if (!token->op && !ft_strcmp(token->content, "{"))
	{
		closing_curly = 0;
		while (token && closing_curly < curly + 1)
		{
			if (!token->op && !ft_strcmp(token->content, "}"))
				closing_curly++;
			token = token->next;
		}
		if (closing_curly == curly + 1)
			return (curly + 1);
	}
	return (curly);
}

static int	parse_level(t_astnode **aroot, char **tokens_lv)
{
	t_astnode	*token;
	t_astnode	*prev;
	int			ret;
	int			curly_opened;

	if (!aroot)
		return (put_error("no arguments", "parse_level"));
	if (!*aroot || !tokens_lv)
		return (0);
	token = *aroot;
	prev = NULL;
	curly_opened = 0;
	while (token)
	{
		curly_opened = curly_update(token, curly_opened);
		if (!curly_opened && token->op && ft_arrstr(tokens_lv, token->op))
		{
			ret = token_handler(&token, prev, *aroot);
			*aroot = token;
			return (ret);
		}
		prev = token;
		token = token->next;
	}
	return (-1);
}

int	ast_parser(t_astnode **aroot)
{
	int			ret;
	size_t		lvl;
	static char	*tokens[3][3] = {
		{";", "&", NULL },
		{"&&", "||", NULL },
		{"|", NULL, NULL }
	};

	lvl = 0;
	if (!*aroot)
		return (0);
	ret = parse_curly_braces(aroot);
	if (ret)
		return (ret);
	ret = parse_all_parentheses(*aroot);
	if (ret)
		return (ret);
	while (lvl < 3)
	{
		ret = parse_level(aroot, tokens[lvl]);
		if (ret != -1)
			return (ret);
		lvl++;
	}
	return (0);
}
