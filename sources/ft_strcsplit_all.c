/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcsplit_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:49:44 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/06 18:07:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

static t_list	*get_next_split(char *s, size_t clen)
{
	t_list	*lmnt;

	if (!s)
		return (NULL);
	lmnt = (t_list *)malloc(sizeof(t_list));
	if (!lmnt)
		return (NULL);
	if (!clen)
		lmnt->content = ft_strdup(s);
	else
		lmnt->content = ft_strndup(s, clen - 1);
	if (!lmnt->content)
	{
		free(lmnt);
		return (NULL);
	}
	lmnt->next = NULL;
	return (lmnt);
}

char	**ft_strcsplit_all(char *s, char c)
{
	t_list	*head;
	t_list	*lmnt;
	size_t	clen;
	char	**split;

	clen = ft_strclen_unquoted(s, c, "\\'\"");
	head = get_next_split(s, clen);
	if (!head)
		return (NULL);
	lmnt = head;
	s += clen;
	while (clen)
	{
		clen = ft_strclen_unquoted(s, c, "\\'\"");
		lmnt->next = get_next_split(s, clen);
		lmnt = lmnt->next;
		s += clen;
	}
	split = ft_lst_to_strarr(head);
	ft_lstfree(head);
	return (split);
}
