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

static int	curly_parser(t_astnode *head)
{
	t_astnode	*node;
	int			curly_count;

	node = head;
	curly_count = 1;
	while (node->next)
	{
		if (!node->next->op && !ft_strcmp(node->next->content, "{"))
			curly_count++;
		else if (!node->next->op && !ft_strcmp(node->next->content, "}"))
			curly_count--;
		if (!curly_count)
			break ;
		node = node->next;
	}
	if (!node->next)
		return (put_error("curly not closed", "{"));
	if (!(head->op = ft_strdup("{}")))
		return (put_error("malloc failed", "curly_parser"));
	free(head->content);
	head->content = head->next;
	head->next = node->next->next;
	free_node(node->next);
	node->next = NULL;
	return (ast_parser((t_astnode **)&head->content));
}

int			parse_curly_braces(t_astnode **aroot)
{
	int			ret;
	t_astnode	*node;

	if (!aroot || !*aroot)
		return (put_error("no arguments", "parse_curly_braces"));
	node = *aroot;
	if (!node->op)
	{
		if (!ft_strcmp(node->content, "}"))
			return (put_error("nothing to close", "}"));
		if (!ft_strcmp(node->content, "{"))
			if ((ret = curly_parser(node)))
				return (ret);
	}
	return (0);
}
