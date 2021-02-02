/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:17:26 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:17:27 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **alst, size_t id)
{
	t_list	*prev;
	t_list	*lmnt;
	size_t	i;

	if (!alst || !*alst || id >= ft_lstlen(alst))
		return (NULL);
	if (!id || !(*alst)->next)
	{
		lmnt = *alst;
		*alst = lmnt->next;
		lmnt->next = NULL;
		return (lmnt);
	}
	prev = *alst;
	lmnt = prev->next;
	i = 0;
	while (++i < id)
	{
		prev = lmnt;
		lmnt = lmnt->next;
	}
	prev->next = lmnt->next;
	lmnt->next = NULL;
	return (lmnt);
}
