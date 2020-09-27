/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:14:20 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/19 13:23:37 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		diff;

	if (!n)
		return (0);
	i = 1;
	diff = (int)((unsigned char)*s1 - (unsigned char)*s2);
	while (!diff && *s1 && *s2 && i < n)
	{
		i++;
		s1++;
		s2++;
		diff = (int)((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (diff);
}
