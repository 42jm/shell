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

#include "21sh.h"

static int	handle_separ(t_astnode *token, t_astnode *prev, t_astnode *head)
{
	if (!prev)
		return (put_error("nothing before token", token->op));
	prev->next = NULL;
	if (ast_parser(&head))
		return (1);
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

static int	parse_level(t_astnode **aroot, char **tokens_lv)
{
	t_astnode	*token;
	t_astnode	*prev;
	int			ret;

	if (!aroot)
		return (put_error("no arguments", "parse_level"));
	if (!*aroot || !tokens_lv)
		return (0);
	token = *aroot;
	prev = NULL;
	while (token)
	{
		if (token->op && ft_arrstr(tokens_lv, token->op))
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

int			ast_parser(t_astnode **aroot)
{
	int			ret;
	size_t		lvl;
	static char	*tokens[3][3] = {
		{ ";", "&", NULL },
		{ "&&", "||", NULL },
		{ "|", NULL, NULL }
	};

	lvl = 0;
	while (lvl < 3)
	{
		ret = parse_level(aroot, tokens[lvl]);
		if (ret != -1)
			return (ret);
		lvl++;
	}
	return (0);
}
