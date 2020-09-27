/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_toggle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:40:28 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/08 14:14:17 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	endian_toggle(void *adr, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	tmp;

	i = 0;
	ptr = (unsigned char *)adr;
	while (i < n / 2)
	{
		tmp = ptr[i];
		ptr[i] = ptr[n - i - 1];
		ptr[n - i - 1] = tmp;
		i++;
	}
}
