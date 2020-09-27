/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:22 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:16:23 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *lmnt)
{
	t_list	*lst;

	if (alst)
	{
		if (*alst)
		{
			lst = *alst;
			while (lst->next)
				lst = lst->next;
			lst->next = lmnt;
		}
		else
			*alst = lmnt;
	}
}
