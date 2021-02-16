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
	ret = field_add(node, len);
	if (ret)
		return (ret);
	return (split_field(node->next, afields));
}

int	clean_fields(t_astnode **ap, t_astnode **an, t_astnode **ah, int i)
{
	char	*str;

	if (i < 0)
		return (0);
	while (i--)
	{
		if (remove_empty_field(*ap, an, ah))
			continue ;
		str = remove_quotes((char *)((*an)->content));
		if (!str)
			return (put_error("malloc failed", "clean_fields"));
		free((*an)->content);
		(*an)->content = str;
		*ap = *an;
		*an = (*an)->next;
	}
	return (0);
}

static int	exp_word(t_astnode **ah, t_astnode **an, t_astnode **ap, int *af)
{
	int	ret;

	ret = expand_tilde(*an);
	if (!ret)
		ret = expand_param(*an);
	if (!ret)
		ret = split_field(*an, af);
	if (!ret)
		ret = clean_fields(ap, an, ah, *af);
	return (ret);
}

int	expand_words(t_astnode **ahead)
{
	int			ret;
	int			fields;
	t_astnode	*prev;
	t_astnode	*node;

	if (!ahead || !*ahead)
		return (0);
	prev = NULL;
	node = *ahead;
	ret = 0;
	while (!ret && node)
	{
		fields = 0;
		if (node->op)
		{
			prev = node;
			node = node->next;
			continue ;
		}
		ret = exp_word(ahead, &node, &prev, &fields);
	}
	return (ret);
}
