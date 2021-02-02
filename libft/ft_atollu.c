/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atollu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 09:42:23 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/29 11:40:26 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

uint64_t	ft_atollu(char *s)
{
	uint64_t	sum;

	while (*s && ft_strchr("\n\v\t\r\f ", *s))
		s++;
	sum = 0;
	while (ft_isdigit((int)*s))
	{
		sum = sum * 10 + (uint64_t)(*s - '0');
		s++;
	}
	return (sum);
}
