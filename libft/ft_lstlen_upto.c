/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen_upto.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:18:30 by jmbomeyo          #+#    #+#             */
/*   Updated: 2020/10/01 17:45:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstlen_upto(t_list *head, t_list *tail)
{
	size_t	i;
	t_list	*lmnt;

	i = 0;
	lmnt = head;
	while (lmnt)
	{
		i++;
		if (lmnt == tail)
			return (i);
		lmnt = lmnt->next;
	}
	return (0);
}
