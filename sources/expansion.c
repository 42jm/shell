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

#include "21sh.h"

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
	len = ft_stralen_unquoted(node->content, "\t ");
	(*afields)++;
	if (!len)
		return (0);
	if ((ret = field_add(node, len)))
		return (ret);
	return (split_field(node->next, afields));
}

static int	remove_quotes(t_astnode *node)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	tmp = node->content;
	while ((len = ft_stralen_unquoted(tmp + i, "\"'\\")))
	{
		i += len - 1;
		len = 1;
		if (tmp[i] != '\\')
		{
			len = quotationlen(tmp + i, "\"'\\");
			if (!len && ++i)
				continue ;
			if (ft_strdrop_inplace(&tmp, i + len - 1, i + len))
				return (put_error("malloc failed (closing)", "remove_quotes"));
			len -= 2;
		}
		if (ft_strdrop_inplace(&tmp, i, i + 1))
			return (put_error("malloc failed (opening)", "remove_quotes"));
		i += len;
	}
	node->content = tmp;
	return (0);
}

int			expand_word(t_astnode *node)
{
	int	ret;
	int	fields;

	while (node)
	{
		if (node->op)
		{
			node = node->next;
			continue ;
		}
		if ((ret = expand_tilde(node)))
			return (ret);
		if ((ret = expand_param(node)))
			return (ret);
		fields = 0;
		if ((ret = split_field(node, &fields)))
			return (ret);
		while (fields--)
		{
			if ((ret = remove_quotes(node)))
				return (ret);
			node = node->next;
		}
	}
	return (0);
}
