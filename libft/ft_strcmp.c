/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 14:14:20 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 14:34:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	diff;

	diff = (int)((unsigned char)*s1 - (unsigned char)*s2);
	while (!diff && *s1 && *s2)
	{
		s1++;
		s2++;
		diff = (int)((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (diff);
}
