/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdrop_inplace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:51 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/09/23 12:16:52 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strdrop_inplace(char **as, size_t i, size_t j)
{
	char	*tmp;

	if (!as || !*as)
		return (1);
	tmp = ft_strdrop(*as, i, j);
	if (!tmp)
		return (2);
	free(*as);
	*as = tmp;
	return (0);
}
