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

static t_astnode	*get_command_name(t_astnode *node, t_astnode **prev)
{
	while (node)
	{
		if (!node->op && node->content && !ft_strchr(node->content, '='))
			break ;
		if (node->op && (ft_strchr(node->op, '<') || ft_strchr(node->op, '>')))
		{
			*prev = node;
			node = node->next;
		}
		if (node)
		{
			*prev = node;
			node = node->next;
		}
	}
	return (node);
}

int	expand_alias(t_astnode **at)
{
	t_astnode	*node;
	t_astnode	*prev;
	char		*alias;
	t_astnode	*aliasnode;
	int			ret;

	prev = NULL;
	node = get_command_name(*at, &prev);
	if (!node || !node->content)
		return (astexec_simplecmd(at));
	alias = ft_get_alias(node->content);
	if (!alias)
		return (astexec_simplecmd(at));
	if (!*alias)
	{
		free(node->content);
		node->content = ft_strdup("");
		return (astexec_simplecmd(at));
	}
	aliasnode = NULL;
	ret = alias_insert_node(&aliasnode, alias, at, prev);
	if (ret)
		return (ret);
	aliasnode->next = node->next;
	free_node(node);
	node = aliasnode->next;
	return (astexec_simplecmd(at));
}
