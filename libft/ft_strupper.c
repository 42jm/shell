/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:19:06 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:19:07 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupper(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if ('a' <= str[i] && 'Z' <= str[i])
			str[i] = (char)ft_toupper((int)str[i]);
		i++;
	}
	return (str);
}
