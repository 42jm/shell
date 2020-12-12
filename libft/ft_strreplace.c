/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:40:59 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/24 16:04:22 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *str, char *needle, size_t start, size_t end)
{
	char	*dropped;
	char	*replaced;

	dropped = ft_strdrop(str, start, end);
	if (!dropped)
		return (NULL);
	if (!needle)
		return (dropped);
	replaced = ft_strninsert(dropped, needle, start);
	free(dropped);
	return (replaced);
}
