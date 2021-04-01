/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/02/16 21:29:17 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_42sh.h"

int	remove_empty_field(t_astnode *prev, t_astnode **anode, t_astnode **ahead)
{
	t_astnode	*node;
	t_astnode	*next;
	char		*str;

	node = *anode;
	str = node->content;
	if (*str)
		return (0);
	next = node->next;
	free_node(node);
	if (prev)
		prev->next = next;
	else
		*ahead = next;
	*anode = next;
	return (1);
}

static int	exprm_should_drop_first_quote(char *str, int inside_doubles)
{
	if (!str || !*str)
		return (0);
	if (*str != '\\')
		return (1);
	if (!inside_doubles)
		return (1);
	if (str[1] && ft_strchr("$`\\\"\n", str[1]))
		return (1);
	return (0);
}

static char	*remove_quotes_non_recursive(char *ptr, char *quotes, int indoubles)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	str = ft_strdup(ptr);
	len = ft_stralen_unquoted(str, quotes);
	while (str && len)
	{
		i += len - 1;
		len = 1;
		if (str[i] != '\\')
		{
			len = quotationlen(str + i, quotes);
			if (!len && ++i)
				continue ;
			ft_strdrop_inplace(&str, i + len - 1, i + len);
			len -= 2;
		}
		if (exprm_should_drop_first_quote(str + i, indoubles))
			ft_strdrop_inplace(&str, i, i + 1);
		i += len;
		len = ft_stralen_unquoted(str + i, quotes);
	}
	return (str);
}

char	*remove_quotes(char *ptr)
{
	char	*str;
	char	*tmp;

	str = remove_quotes_non_recursive(ptr, "\"'\\", 0);
	if (!str)
		return (NULL);
	if (*ptr == '"')
	{
		tmp = str;
		str = remove_quotes_non_recursive(str, "\\", 1);
		free(tmp);
	}
	return (str);
}
