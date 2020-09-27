/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_strarr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:06:09 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:12:02 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_strarr(t_list *lst)
{
	size_t	len;
	char	**strarr;
	size_t	i;

	len = ft_lstlen(&lst);
	strarr = (char **)malloc(sizeof(*strarr) * (len + 1));
	if (!strarr)
		return (NULL);
	i = 0;
	while (lst)
	{
		strarr[i] = ft_strdup((char *)lst->content);
		lst = lst->next;
		i++;
	}
	strarr[i] = NULL;
	return (strarr);
}
