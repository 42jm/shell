/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:18:30 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:18:31 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind_head(t_list **alst, void *content, size_t len)
{
	t_list	*lst;

	if (!alst)
		return (NULL);
	lst = *alst;
	while (lst)
	{
		if (len <= lst->content_size && !ft_memcmp(content, lst->content, len))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}
