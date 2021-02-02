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

static long long int	sub_iter(char *str, long long int sum)
{
	if (ft_isdigit((int)*str))
		return (sub_iter(str + 1, sum * 10 + (long long int)(*str - '0')));
	return (sum);
}

int	ft_atoi(const char *str)
{
	char	*s;
	int		sign;

	s = (char *)str;
	sign = 1;
	while (*s && ft_strchr("\n\v\t\r\f ", *s))
		s++;
	if (*s && ft_strchr("+-", *s))
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	return (sign * (int)sub_iter(s, 0));
}
