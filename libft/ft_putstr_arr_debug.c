/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:17:05 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:17:06 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_arr(char **arr)
{
	size_t	n;
	size_t	i;

	n = ft_strlen_arr((const char **)arr);
	i = 0;
	while (i < n)
	{
		ft_putchar('[');
		ft_putnbr(i);
		ft_putstr("] ");
		ft_putendl(arr[i]);
		i++;
	}
}
