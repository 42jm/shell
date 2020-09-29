/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:56:17 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/11 11:56:26 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_pow(int n, int exp)
{
	int					i;
	unsigned long long	res;

	if (!exp)
		return (1);
	i = 1;
	res = n;
	while (i++ < exp)
		res *= n;
	return (res);
}
