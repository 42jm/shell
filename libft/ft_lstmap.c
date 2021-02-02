/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:10:25 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 10:19:11 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *lmnt))
{
	t_list	*new;
	t_list	*out;

	if (!lst)
		return (NULL);
	new = (*f)(lst);
	out = new;
	lst = lst->next;
	while (lst)
	{
		new->next = (*f)(lst);
		if (!new->next)
			return (NULL);
		new = new->next;
		lst = lst->next;
	}
	return (out);
}
