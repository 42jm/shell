/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 18:16:10 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

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

int	remove_quotes(t_astnode *node)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	tmp = node->content;
	len = ft_stralen_unquoted(tmp + i, "\"'\\");
	while (len)
	{
		i += len - 1;
		len = 1;
		if (tmp[i] != '\\')
		{
			len = quotationlen(tmp + i, "\"'\\");
			if (!len && ++i)
				continue ;
			ft_strdrop_inplace(&tmp, i + len - 1, i + len);
			len -= 2;
		}
		ft_strdrop_inplace(&tmp, i, i + 1);
		i += len;
		len = ft_stralen_unquoted(tmp + i, "\"'\\");
	}
	node->content = tmp;
	return (0);
}
