/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 11:13:00 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/20 11:44:00 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_toupper(int i)
{
	char	c;

	c = (char)i;
	if ('a' <= c && c <= 'z')
		return ((int)(c + 'A' - 'a'));
	return (c);
}
