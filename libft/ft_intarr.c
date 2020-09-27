/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:25:20 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/11 16:43:41 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint64_t	*ft_intarr(uint64_t len, ...)
{
	uint64_t	*intarr;
	va_list		ap;
	uint64_t	i;

	intarr = (uint64_t *)malloc(sizeof(uint64_t) * len);
	ft_bzero(intarr, sizeof(uint64_t) * len);
	va_start(ap, len);
	i = 0;
	while (i < len)
	{
		intarr[i] = va_arg(ap, uint64_t);
		i++;
	}
	return (intarr);
}
