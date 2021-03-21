/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 09:42:23 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 10:59:46 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi_strict(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr && ft_isdigit(*ptr))
		ptr++;
	if (*ptr)
		return (-1);
	return (ft_atoi(str));
}
