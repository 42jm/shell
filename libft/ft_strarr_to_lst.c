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

t_list	*ft_strarr_to_lst(char **arr)
{
	t_list	*lst;
	t_list	*ptr;
	size_t	i;

	if (!arr || !arr[0])
		return (NULL);
	i = 0;
	lst = ft_lstnew((void const *)arr[i], ft_strlen(arr[i]) + 1);
	ptr = lst;
	while (ptr && arr[++i])
	{
		ptr->next = ft_lstnew((void const *)arr[i], ft_strlen(arr[i]) + 1);
		ptr = ptr->next;
	}
	return (lst);
}
