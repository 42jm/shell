/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/15 13:32:30 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

static char	*ast_fields_to_str(char sep, t_astnode *node)
{
	char	*ret;
	char	*tmp;

	if (!node)
		return (NULL);
	ret = ft_strdup(node->content);
	while (node->next)
	{
		node = node->next;
		tmp = ret;
		ret = ft_strcjoin(sep, ret, node->content);
		if (tmp)
			free(tmp);
	}
	return (ret);
}

char	*expand_str(char *str)
{
	t_astnode	*node;
	char		*ret;

	if (!str)
		return (NULL);
	node = token_new(NULL);
	node->content = ft_strdup(str);
	if (expand_words(&node))
	{
		free_ast(node);
		return (NULL);
	}
	ret = ast_fields_to_str(' ', node);
	free_ast(node);
	return (ret);
}
