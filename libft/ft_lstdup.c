/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 09:53:03 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 10:21:19 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*dup;
	t_list	*dup_head;

	ft_putendl("\t0");
	if (!lst)
		return (NULL);
	ft_putendl("\t1");
	dup = ft_lstnew(lst->content, lst->content_size);
	dup_head = dup;
	ft_putendl("\t2");
	while (lst->next)
	{
		ft_putendl("\t2.1");
		lst = lst->next;
		dup->next = ft_lstnew(lst->content, lst->content_size);
		dup = dup->next;
	}
	ft_putendl("\t3");
	return (dup_head);
}
