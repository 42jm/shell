/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putusage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 12:57:46 by jmbomeyo          #+#    #+#             */
/*   Updated: 2019/10/05 13:02:13 by jmbomeyo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putusage(char *exename, char *usage)
{
	ft_putstr_fd("usage: ", 2);
	ft_putstr_fd(exename, 2);
	ft_putchar_fd(' ', 2);
	ft_putendl_fd(usage, 2);
	return (EXIT_FAILURE);
}
