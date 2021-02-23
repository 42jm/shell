/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmbomeyo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:16:49 by jmbomeyo          #+#    #+#             */
/*   Updated: 2021/02/23 18:47:35 by quegonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell21.h"

void	sighandle_ignore(int signum)
{
	(void)signum;
}

void	sighandle_int(int signum)
{
	(void)signum;
	ft_putchar('\n');
	env_set("?", "130", 0);
}
