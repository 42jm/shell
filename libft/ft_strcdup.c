/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:18:54 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:18:57 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(char *str, char chr)
{
	int		i;
	char	*cdup;

	i = 0;
	while (str[i] && str[i] != chr)
		i++;
	if (!str[i])
		return (ft_strdup(str));
	if (!(cdup = ft_strnew(i)))
		return (NULL);
	while (--i >= 0)
		cdup[i] = str[i];
	return (cdup);
}
