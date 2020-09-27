/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcrop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:51 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:16:52 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcrop(char *str, size_t start, size_t end)
{
	char	*crop;
	size_t	i;

	if (end == 0 || end < start || ft_strlen(str) < end)
		return (NULL);
	if (!(crop = (char *)malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	crop[end - start] = '\0';
	i = 0;
	while (start + i < end)
	{
		crop[i] = str[start + i];
		i++;
	}
	return (crop);
}
