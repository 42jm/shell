/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_strarr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static size_t	ft_astlen(t_astnode *node)
{
	size_t	len;

	len = 0;
	while (node)
	{
		len++;
		node = node->next;
	}
	return (len);
}

char			**ast_to_strarr(t_astnode *node)
{
	size_t	len;
	char	**strarr;
	size_t	i;

	len = ft_astlen(node);
	strarr = (char **)malloc(sizeof(*strarr) * (len + 1));
	if (!strarr)
		return (NULL);
	i = 0;
	while (node)
	{
		strarr[i] = ft_strdup((char *)node->content);
		node = node->next;
		i++;
	}
	strarr[i] = NULL;
	return (strarr);
}
