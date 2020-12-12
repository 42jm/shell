/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 17:09:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/23 11:34:08 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_arrnstr(char **arr, char *s, size_t len)
{
	while (arr && *arr && s && *s)
	{
		if (!ft_strncmp(*arr, s, len))
			return (*arr);
		arr++;
	}
	return (NULL);
}
