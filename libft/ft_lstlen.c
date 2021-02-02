/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:16:12 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstlen(t_list **alst)
{
	size_t	len;
	t_list	*lst;

	len = 0;
	if (alst)
	{
		lst = *alst;
		len++;
		lst = lst->next;
		while (lst)
		{
			len++;
			lst = lst->next;
		}
	}
	return (len);
}
