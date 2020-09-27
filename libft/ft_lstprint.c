/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:35 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:16:37 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **alst, void (*put_lmnt)(t_list *lmnt))
{
	t_list	*lst;
	size_t	i;

	lst = *alst;
	i = 0;
	while (lst)
	{
		ft_putnbr(i);
		ft_putstr(" [");
		ft_putnbr(lst->content_size);
		ft_putchar(']');
		put_lmnt(lst);
		ft_putchar('\n');
		lst = lst->next;
		i++;
	}
}
