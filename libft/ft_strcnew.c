/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:13:51 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 12:32:15 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strcnew(size_t sz, char c)
{
	char	*str;
	size_t	i;

	str = (char *)malloc((sz + 1) * sizeof(char));
	i = -1;
	if (str)
	{
		while (++i < sz)
			str[i] = c;
		str[sz] = '\0';
	}
	return (str);
}
