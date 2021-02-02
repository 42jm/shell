/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astparse_parentheses.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/13 12:29:36 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

t_astnode	*paren_count(t_astnode *node)
{
	int		c;

	c = 1;
	while (node->next)
	{
		if (node->next->op && !ft_strcmp(node->next->op, "("))
			c++;
		else if (node->next->op && !ft_strcmp(node->next->op, ")"))
			c--;
		if (!c)
			break ;
		node = node->next;
	}
	return (node);
}

static int	parentheses_parser(t_astnode *head)
{
	t_astnode	*node;
	char		*new_op;

	node = paren_count(head);
	if (!node->next)
		return (put_error("no closing parentheses", head->op));
	if (head == node)
		return (put_error("empty parentheses", head->op));
	new_op = ft_strjoin(head->op, ")");
	if (!new_op)
		return (put_error("malloc failed", "parentheses_parser"));
	free(head->op);
	head->op = new_op;
	head->content = head->next;
	head->next = node->next->next;
	free_node(node->next);
	node->next = NULL;
	return (ast_parser((t_astnode **)&head->content));
}

int	parse_all_parentheses(t_astnode *head)
{
	int			ret;
	t_astnode	*node;

	node = head;
	while (node)
	{
		if (node->op)
		{
			ret = 0;
			if (!ft_strcmp(node->op, ")"))
				return (put_error("nothing to close", ")"));
			else if (!ft_strcmp(node->op, "("))
				ret = parentheses_parser(node);
			else if (!ft_strcmp(node->op, "<("))
				ret = parentheses_parser(node);
			else if (!ft_strcmp(node->op, ">("))
				ret = parentheses_parser(node);
			if (ret)
				return (ret);
		}
		node = node->next;
	}
	return (0);
}
