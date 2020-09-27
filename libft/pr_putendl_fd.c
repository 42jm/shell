/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pr_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 11:20:25 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/02/21 12:53:54 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pr_putendl_fd(char const *s, int fd)
{
	if (pr_putstr_fd(s, fd))
		return (1);
	if (pr_putstr_fd("\n", fd))
		return (2);
	return (0);
}
