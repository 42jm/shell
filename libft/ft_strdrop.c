/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:51 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:16:52 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdrop(char *str, size_t i, size_t j)
{
	size_t	len;
	char	*drop;

	len = ft_strlen(str);
	if (j == 0 || j < i || len < j)
		return (NULL);
	drop = ft_strnew(i + (len - j));
	if (!drop)
		return (NULL);
	ft_strncpy(drop, str, i);
	ft_strcpy(drop + i, str + j);
	return (drop);
}
