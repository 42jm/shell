/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_to_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_strarr_to_lst(char **strarr)
{
	t_list	*lst;
	t_list	*ptr;
	size_t	i;

	if (!strarr || !strarr[0])
		return (NULL);
	i = 0;
	lst = ft_lstnew((void const *) strarr[i], ft_strlen(strarr[i]));
	ptr = lst;
	while (ptr && strarr[++i])
	{
		ptr->next = ft_lstnew((void const *) strarr[i], ft_strlen(strarr[i]));
		ptr = ptr->next;
	}
	return (lst);
}
