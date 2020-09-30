/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:18:30 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:18:31 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstget_id(t_list **alst, void *content, size_t content_size)
{
	size_t	i;
	t_list	*lst;

	if (alst)
	{
		i = 0;
		lst = *alst;
		while (lst)
		{
			if (content_size == lst->content_size \
			&&	!ft_memcmp(content, lst->content, content_size))
				return (i);
			lst = lst->next;
			i++;
		}
	}
	return (-1);
}
