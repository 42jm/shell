/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_alias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quegonza.h"
#include "header_42sh.h"

int	alias_insert_node(t_astnode **node, char *str, t_astnode **at, t_astnode *p)
{
	int	ret;

	ret = ast_lexer(str, node);
	if (!ret)
		ret = ast_parser(node);
	if (ret)
		return (ret);
	if (p)
		p->next = *node;
	else
		*at = *node;
	while ((*node)->next)
		*node = (*node)->next;
	return (0);
}

int	expand_alias(t_astnode **at)
{
	t_astnode	*node;
	t_astnode	*prev;
	char		*alias;
	t_astnode	*aliasnode;
	int			ret;

	prev = NULL;
	node = *at;
	while (node)
	{
		if (node->op)
			break ;
		alias = ft_get_alias(node->content);
		if (!alias)
			break ;
		aliasnode = NULL;
		ret = alias_insert_node(&aliasnode, alias, at, prev);
		if (ret)
			return (ret);
		aliasnode->next = node->next;
		free_node(node);
		prev = aliasnode;
		node = aliasnode->next;
	}
	return (astexec_simplecmd(at));
}
