/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:03:25 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 10:19:44 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *lmnt))
{
	if (lst && f)
	{
		(*f)(lst);
		lst = lst->next;
		while (lst)
		{
			(*f)(lst);
			lst = lst->next;
		}
	}
}
