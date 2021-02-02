/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:14:20 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 14:34:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	get_diff(char c1, char c2)
{
	unsigned char	uc1;
	unsigned char	uc2;

	uc1 = (unsigned char)ft_tolower((int)c1);
	uc2 = (unsigned char)ft_tolower((int)c2);
	return ((int)(uc1 - uc2));
}

int	ft_strcmp_ci(const char *s1, const char *s2)
{
	int	diff;

	diff = get_diff(*s1, *s2);
	while (!diff && *s1 && *s2)
	{
		s1++;
		s2++;
		diff = get_diff(*s1, *s2);
	}
	return (diff);
}
