/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static int	field_add(t_astnode *node, size_t n)
{
	t_astnode	*og_next;
	char		*og_word;

	og_next = node->next;
	og_word = node->content;
	node->content = ft_strndup(og_word, n - 1);
	if (!node->content)
	{
		node->content = og_word;
		return (put_error("malloc failed", "field_add"));
	}
	node->next = token_new(NULL);
	if (!node->next)
		return (put_error("failed to create new field", "field_add"));
	node->next->op = NULL;
	node->next->next = og_next;
	node->next->content = ft_strdup(og_word + n);
	if (!node->next->content)
	{
		node->next->content = og_word;
		return (put_error("malloc failed", "field_add"));
	}
	free(og_word);
	return (0);
}

static int	split_field(t_astnode *node, int *afields)
{
	size_t		len;
	int			ret;

	if (!node || !node->content || !afields)
		return (put_error("no arguments", "field_split"));
	len = ft_stralen_unquoted(node->content, "\t \n");
	(*afields)++;
	if (!len)
		return (0);
	if ((ret = field_add(node, len)))
		return (ret);
	return (split_field(node->next, afields));
}

int			clean_fields(t_astnode *prev, t_astnode **anode, int fields)
{
	int			ret;

	if (fields < 0)
		return (0);
	while (fields--)
	{
		if (remove_empty_field(prev, anode))
			continue ;
		if ((ret = remove_quotes(*anode)))
			return (ret);
		prev = *anode;
		*anode = (*anode)->next;
	}
	return (0);
}

int			expand_word(t_astnode *node)
{
	int			ret;
	int			fields;
	t_astnode	*prev;

	prev = NULL;
	while (node)
	{
		fields = 0;
		if (node->op)
		{
			prev = node;
			node = node->next;
			continue ;
		}
		if ((ret = expand_tilde(node)) \
		|| (ret = expand_param(node)) \
		|| (ret = split_field(node, &fields)) \
		|| (ret = clean_fields(prev, &node, fields)))
			return (ret);
	}
	return (0);
}
