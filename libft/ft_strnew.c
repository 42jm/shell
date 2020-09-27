/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:13:51 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 12:32:15 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnew(size_t sz)
{
	char	*new;
	size_t	i;

	new = (char *)malloc((sz + 1) * sizeof(char));
	i = -1;
	if (new)
		while (++i < sz + 1)
			new[i] = '\0';
	return (new);
}
